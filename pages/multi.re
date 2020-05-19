type user = {
  name: string,
  guid: string,
};

type state = {user: option(user)};

type action =
  | CreateUser(string);

let reducer = (_state, action) =>
  switch (action) {
  | CreateUser(name) => {user: Some({name, guid: "some guid"})}
  };

[@react.component]
let make = () => {
  let initialState = React.useMemo(() => {user: None});
  let (state, dispatch) = React.useReducer(reducer, initialState);
  <div className="w-screen h-screen flex justify-center items-center">
    {switch (state.user) {
     | Some(user) => S.str("Welcome back " ++ user.name)
     | None => <Login onSubmitName={name => dispatch(CreateUser(name))} />
     }}
  </div>;
};

let default = make;