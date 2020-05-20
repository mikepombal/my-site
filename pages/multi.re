open Types;

type state = {
  user: option(user),
  isMount: bool,
};

type action =
  | CreateUser(string)
  | LoadUser(option(user));

let reducer = (state, action) =>
  switch (action) {
  | CreateUser(name) =>
    let uuid = Uuid.generateUUID();
    Storage.saveUserToStorage(name, uuid);
    {...state, user: Some({name, uuid})};
  | LoadUser(user) => {isMount: true, user}
  };

[@react.component]
let make = () => {
  let initialState = React.useMemo(() => {isMount: false, user: None});
  let (state, dispatch) = React.useReducer(reducer, initialState);
  React.useEffect1(
    () => {
      Storage.getUserFromStorage()->LoadUser |> dispatch;
      None;
    },
    [||],
  );

  <div className="w-screen h-screen flex justify-center items-center">
    {switch (state.isMount, state.user) {
     | (false, _) => ReasonReact.string("Please wait while loading data")
     | (true, Some(user)) =>
       S.str("Welcome back " ++ user.name ++ "(" ++ user.uuid ++ ")")
     | (true, None) =>
       <Login onSubmitName={name => CreateUser(name) |> dispatch} />
     }}
  </div>;
};

let default = make;