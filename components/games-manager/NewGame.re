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

type state = {
  gameId: option(int),
  users: list(int),
};

type action =
  | SelectGame(int)
  | SelectUser(int);

let reducer = (state, action) => {
  switch (action) {
  | SelectGame(gameId) => {...state, gameId: Some(gameId)}
  | SelectUser(userId) => {
      ...state,
      users:
        Belt.List.some(state.users, id => id == userId)
          ? Belt.List.keep(state.users, id => id != userId)
          : Belt.List.add(state.users, userId),
    }
  };
};

[@react.component]
let make = (~goBackHome, ~userId) => {
  let (state, dispatch) =
    React.useReducer(reducer, {gameId: None, users: []});
  let (simple, _) = useQuery(GamesListQuery.definition);
  let (activeUsers, _) =
    ApolloHooks.useSubscription(ActiveUsersSubscription.definition);

  <div className="flex flex-col">
    {S.str("Preparing new game!")}
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
                       switch (state.gameId) {
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
      <div>
        {switch (activeUsers) {
         | Loading =>
           <div> {ReasonReact.string("Loading list active users")} </div>
         | Data(data) =>
           <ul>
             {Array.map(
                user =>
                  switch (user##user_id, user##username) {
                  | (Some(id), Some(username)) when id != userId =>
                    <li key={string_of_int(id)}>
                      <button
                        className={
                          "px-6 py-2 flex justify-center align-middle mb-2 w-full focus:outline-none"
                          ++ (
                            Belt.List.some(state.users, u => u == id)
                              ? " bg-green-500" : " bg-gray-300"
                          )
                        }
                        onClick={_event => SelectUser(id) |> dispatch}>
                        {S.str(username)}
                      </button>
                    </li>
                  | (_, _) => React.null
                  },
                data##active_users,
              )
              |> S.arr}
           </ul>
         | NoData => S.str("No data")
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