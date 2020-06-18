// const fetch = require("node-fetch");

// const HASURA_OPERATION = `
// query getUser($uuid: uuid!){
//   users_by_pk(token: $uuid) {
//     token
//     username
//   }
// }
// `;

// const execute = async (variables, session_variables) => {
//   console.log("starting execute function: ", session_variables);
//   const fetchResponse = await fetch(
//     "https://mikepombal.herokuapp.com/v1/graphql",
//     {
//       method: "POST",
//       body: JSON.stringify({
//         query: HASURA_OPERATION,
//         variables,
//       }),
//       headers: session_variables,
//     }
//   );
//   console.log("cool, now getting the data");
//   const data = await fetchResponse.json();
//   console.log("DEBUG: ", data);
//   return data;
// };

const ACTION_SECRET = "action_secret";

export default async function handler(req, res) {
  console.log("Welcome to testapi: ");

  if (process.env.ACTION_SECRET_ENV !== req.headers[ACTION_SECRET]) {
    return res.status(403).json({
      status: 403,
      error: "Hasura action access not allowed",
    });
  }

  console.log("req.body.input: ", req.body.input);
  console.log("req.body.session_variables: ", req.body.session_variables);
  //   console.log("req.headers[ACTION_SECRET]: ", req.headers[ACTION_SECRET]);

  //   const { uuid } = req.body.input;
  //   console.log(req.headers);
  // const session_variables = req.body.session_variables;

  // const { data, errors } = await execute({ uuid: "0d0fbc2f-3d1c-4add-94e3-a54f3fde7d40" }, session_variables);

  // if (errors) {
  //   console.log("There is an error while trying to get the data");
  //   return res.status(400).json(errors[0]);
  // }

  return res.status(200).json({
    token: "Something to be defined",
    username: "username",
  });
}
