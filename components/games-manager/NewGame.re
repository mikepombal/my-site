open ApolloHooks;

module GamesListQuery = [%graphql
  {|
    query {
      games_type {
        name
      }
    }
  |}
];

module ActiveUsersSubscription = [%graphql
  {|
    subscription {
      active_users {
        username
      }
    }
  |}
];

[@react.component]
let make = (~goBackHome) => {
  let (simple, _) = useQuery(GamesListQuery.definition);
  let (activeUsers, _) =
    ApolloHooks.useSubscription(ActiveUsersSubscription.definition);

  <div className="flex flex-col">
    {S.str("Preparing new game!")}
    <div>
      <div>
        {switch (simple) {
         | Data(data) =>
           S.arr(Array.map(g => S.str(g##name), data##games_type))
         | Loading => S.str("Loading list of games")
         | _ => S.str("Oops something wrong")
         }}
      </div>
      <div>
        {switch (activeUsers) {
         | Loading =>
           <div> {ReasonReact.string("Loading list active users")} </div>
         | Data(data) =>
           S.arr(
             Array.map(
               user =>
                 switch (user##username) {
                 | Some(username) => S.str(username)
                 | None => ReasonReact.null
                 },
               data##active_users,
             ),
           )
         | _ => S.str("Oops something wrong")
         }}
      </div>
    </div>
    <button className="bg-blue-400 text-white" onClick=goBackHome>
      {S.str("Back to Hame")}
    </button>
  </div>;
};

let default = make;