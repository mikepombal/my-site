const fetch = require("node-fetch");

const HASURA_OPERATION = `
query getUser($uuid: uuid!){
  users_by_pk(token: $uuid) {
    token
    username
  }
}
`;

// const execute = async (variables) => {
//   const fetchResponse = await fetch(
//     "https://mikepombal.herokuapp.com/v1/graphql",
//     {
//       method: "POST",
//       body: JSON.stringify({
//         query: HASURA_OPERATION,
//         variables,
//       }),
//     }
//   );
//   const data = await fetchResponse.json();
//   console.log("DEBUG: ", data);
//   return data;
// };

export default function handler(req, res) {
  //   const { uuid } = req.body.input;

  //   const { data, errors } = await execute({ uuid });

  //   if (errors) {
  //     return res.status(400).json(errors[0])
  //   }

  res.status(200).json({ accessToken: "data.users_by_pk.username" });
}
