const fetch = require("node-fetch");

const HASURA_OPERATION = `
query getUser($uuid: uuid!){
  users_by_pk(token: $uuid) {
    token
    username
  }
}
`;

const execute = async (variables, session_variables) => {
  console.log("starting execute function: ", session_variables);
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
  console.log("cool, now getting the data");
  const data = await fetchResponse.json();
  console.log("DEBUG: ", data);
  return data;
};

export default async function handler(req, res) {
  console.log("Welcome to testapi: ");
  const { uuid } = req.body.input;
  console.log(req.headers);
  const session_variables = req.body.session_variables;

  const { data, errors } = await execute({ uuid }, session_variables);

  if (errors) {
    return res.status(400).json(errors[0]);
  }

  res.status(200).json({ accessToken: "data.users_by_pk.username" });
}
