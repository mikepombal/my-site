open ApolloHooks;

module GamesListQuery = [%graphql
  {|
    query {
      games_type {
        id
        name
      }
    }
  |}
];

module ActiveUsersSubscription = [%graphql
  {|
    subscription {
      active_users {
        user_id
        username
      }
    }
  |}
];

type config = {
  gameId: option(int),
  users: list(int),
};

type state =
  | Selection(config)
  | PreparingGame(config);

type action =
  | SelectGame(int)
  | SelectUser(int)
  | CreateGame;

let reducer = (state, action) => {
  switch (state, action) {
  | (Selection(config), SelectGame(gameId)) =>
    Selection({...config, gameId: Some(gameId)})
  | (Selection(config), SelectUser(userId)) =>
    Selection({
      ...config,
      users:
        Belt.List.some(config.users, id => id == userId)
          ? Belt.List.keep(config.users, id => id != userId)
          : Belt.List.add(config.users, userId),
    })
  | (Selection(config), CreateGame) => PreparingGame(config)
  | (_, _) => state
  };
};

[@react.component]
let make = (~goBackHome, ~userId) => {
  let (state, dispatch) =
    React.useReducer(reducer, Selection({gameId: None, users: []}));
  let (simple, _) = useQuery(GamesListQuery.definition);
  //   let (activeUsers, _) =
  //     ApolloHooks.useSubscription(ActiveUsersSubscription.definition);

  React.useEffect1(
    () => {
      switch (state) {
      | PreparingGame(config) =>
        switch (config.gameId) {
        | Some(gameId) =>
          Js.log("Prepare game with id of " ++ string_of_int(gameId));
          ();
        | _ => ()
        }

      | _ => ()
      };
      None;
    },
    [|state|],
  );

  <div className="flex flex-col">
    {switch (state) {
     | Selection(config) =>
       <div className="flex">
         <ul>
           {switch (simple) {
            | Data(data) =>
              Array.map(
                g =>
                  <li key={g##name}>
                    <button
                      className={
                        "px-6 py-2 flex justify-center align-middle mb-2 w-full focus:outline-none"
                        ++ (
                          switch (config.gameId) {
                          | Some(id) when id == g##id => " bg-green-500"
                          | _ => " bg-gray-300"
                          }
                        )
                      }
                      onClick={_event => SelectGame(g##id) |> dispatch}>
                      {S.str(g##name)}
                    </button>
                  </li>,
                data##games_type,
              )
              |> S.arr

            | Loading => S.str("Loading list of games")
            | _ => S.str("Oops something wrong")
            }}
         </ul>
         //  <div>
         //    {switch (activeUsers) {
         //     | Loading =>
         //       <div> {ReasonReact.string("Loading list active users")} </div>
         //     | Data(data) =>
         //       <ul>
         //         {Array.map(
         //            user =>
         //              switch (user##user_id, user##username) {
         //              | (Some(id), Some(username)) when id != userId =>
         //                <li key={string_of_int(id)}>
         //                  <button
         //                    className={
         //                      "px-6 py-2 flex justify-center align-middle mb-2 w-full focus:outline-none"
         //                      ++ (
         //                        Belt.List.some(config.users, u => u == id)
         //                          ? " bg-green-500" : " bg-gray-300"
         //                      )
         //                    }
         //                    onClick={_event => SelectUser(id) |> dispatch}>
         //                    {S.str(username)}
         //                  </button>
         //                </li>
         //              | (_, _) => React.null
         //              },
         //            data##active_users,
         //          )
         //          |> S.arr}
         //       </ul>
         //     | NoData => S.str("No data")
         //     | _ => S.str("Oops something wrong")
         //     }}
         //  </div>
         <button
           className="bg-blue-400 text-white"
           onClick={_ => CreateGame |> dispatch}>
           {S.str("Create Game")}
         </button>
         <button className="bg-blue-400 text-white" onClick=goBackHome>
           {S.str("Back to Hame")}
         </button>
       </div>
     | PreparingGame(_) => S.str("Preparing game...")
     }}
  </div>;
};

let default = make;