open Types;

type state =
  | Loading
  | CreatingUser
  | LoggedIn(user);

type action =
  | CreateUser(string)
  | LoadUser(option(user));

let reducer = (state, action) =>
  switch (state, action) {
  | (Loading, LoadUser(Some(user))) => LoggedIn(user)
  | (Loading, LoadUser(None)) => CreatingUser
  | (Loading, _) => state
  | (CreatingUser, _) => state
  | (LoggedIn(_), _) => state
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, Loading);
  React.useEffect1(
    () => {
      Storage.getUserFromStorage()->LoadUser |> dispatch;
      None;
    },
    [||],
  );

  <div className="w-screen h-screen flex justify-center items-center">
    {switch (state) {
     | Loading => ReasonReact.string("Please wait while loading data")
     | LoggedIn(user) =>
       S.str("Welcome back " ++ user.name ++ "(" ++ user.uuid ++ ")")
     | CreatingUser =>
       <Login onSubmitName={name => CreateUser(name) |> dispatch} />
     }}
  </div>;
};

let default = make;