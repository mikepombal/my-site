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

[@react.component]
let make = (~goBackHome) => {
  let (simple, _) = useQuery(GamesListQuery.definition);

  <div className="flex flex-col">
    {S.str("Preparing new game!")}
    <div>
      {switch (simple) {
       | Data(data) =>
         S.arr(Array.map(g => S.str(g##name), data##games_type))
       | Loading => S.str("Loading list of games")
       | _ => S.str("Oops something wrong")
       }}
    </div>
    <button className="bg-blue-400 text-white" onClick=goBackHome>
      {S.str("Back to Hame")}
    </button>
  </div>;
};

let default = make;