const fetch = require("node-fetch");
const jwt = require("jsonwebtoken");

const HASURA_OPERATION = `
  query getUser($uuid: uuid!) {
    users_by_pk(user_uuid: $uuid) {
      username
      user_id
    }
  }
`;

const execute = async (variables, session_variables) => {
  const fetchResponse = await fetch(
    "https://mikepombal.herokuapp.com/v1/graphql",
    {
      method: "POST",
      body: JSON.stringify({
        query: HASURA_OPERATION,
        variables,
      }),
      headers: session_variables,
    }
  );
  const result = await fetchResponse.json();
  return result;
};

const ACTION_SECRET = "action_secret";

export default async function handler(req, res) {
  if (process.env.ACTION_SECRET_ENV !== req.headers[ACTION_SECRET]) {
    return res.status(403).json({
      status: 403,
      error: "Hasura action access not allowed",
    });
  }

  const { uuid } = req.body.input;
  const session_variables = {
    ...req.body.session_variables,
    "x-hasura-user-id": uuid,
  };

  const { data, errors } = await execute(req.body.input, session_variables);

  if (errors) {
    console.log("There is an error while trying to get the data");
    return res.status(400).json(errors[0]);
  }
  if (!data.users_by_pk) {
    return res.status(400).json({
      status: 403,
      error: "NOT REGISTERED",
    });
  }

  const token = jwt.sign(
    {
      "https://hasura.io/jwt/claims": {
        "x-hasura-allowed-roles": ["manager", "user", "anonymous"],
        "x-hasura-default-role": "user",
        "x-hasura-user-id": uuid,
      },
    },
    process.env.JWT_SECRET_KEY,
    {
      algorithm: process.env.JWT_SECRET_TYPE,
      expiresIn: process.env.JWT_TOKEN_EXPIRES,
    }
  );

  return res.status(200).json({
    token,
    username: data.users_by_pk.username,
    user_id: data.users_by_pk.user_id,
  });
}
