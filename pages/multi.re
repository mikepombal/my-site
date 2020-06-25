open Types;
open ApolloHooks;

let getOrDefault = uuid => uuid->Js.Json.decodeString->Belt.Option.getExn;

module RegisterUserMutation = [%graphql
  {|
    mutation register($uuid: uuid!, $username: String!){
      register (uuid: $uuid, username: $username) {
        token
        username
        user_id
      }
    }
  |}
];

module LoginMutation = [%graphql
  {|
    mutation login($uuid: uuid!) {
      login(uuid: $uuid) {
        token
        username
        user_id
      }
    }
  |}
];

type state =
  | Loading
  | CreatingUser
  | LoggingIn(user)
  | Registering(user)
  | LoggedIn(user)
  | Error;

type action =
  | CreateUser(string)
  | LoadUser(option(user))
  | CompleteRegistration
  | ShowError;

let reducer = (state, action) =>
  switch (state, action) {
  | (Loading, LoadUser(Some(user))) => LoggingIn(user)
  | (Loading, LoadUser(None)) => CreatingUser
  | (Loading, _) => state

  | (CreatingUser, CreateUser(name)) =>
    Registering({name, uuid: Uuid.generateUUID(), userId: (-1)})
  | (CreatingUser, _) => state

  | (LoggingIn(user), CompleteRegistration) => LoggedIn(user)
  | (LoggingIn(_), ShowError) => Error
  | (LoggingIn(_), _) => state

  | (Registering(user), CompleteRegistration) => LoggedIn(user)
  | (Registering(_), _) => state

  | (LoggedIn(_), _) => state

  | (Error, _) => state
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, Loading);
  let (register, _, _) = useMutation(RegisterUserMutation.definition);
  let (login, _, _) = useMutation(LoginMutation.definition);
  React.useEffect1(
    () => {
      switch (state) {
      | Loading => Storage.getUserFromStorage()->LoadUser |> dispatch
      | LoggingIn(user) =>
        let variables =
          LoginMutation.makeVariables(~uuid=Js.Json.string(user.uuid), ());
        login(~variables, ())
        |> Js.Promise.then_(
             (
               result: (
                 Mutation.executionVariantResult(LoginMutation.t),
                 Mutation.executionResult(LoginMutation.t),
               ),
             ) => {
             switch (fst(result)) {
             | Data(data) =>
               Js.log2("The data from the login mutation is", data);
               switch (data##login) {
               | Some(u) =>
                 Storage.saveUserToStorage({
                   name: u##username,
                   userId: u##user_id,
                   uuid: user.uuid,
                 });
                 AccessToken.setAccessToken(u##token);
               | None => ShowError |> dispatch
               };

               CompleteRegistration |> dispatch;
             | _ => ShowError |> dispatch
             };
             Js.Promise.resolve();
           })
        |> Js.Promise.catch(error => {
             Js.log2("Something wrong", error);
             Js.Promise.resolve();
           })
        |> ignore;

      | Registering(user) =>
        let variables =
          RegisterUserMutation.makeVariables(
            ~uuid=Js.Json.string(user.uuid),
            ~username=user.name,
            (),
          );
        register(~variables, ())
        |> Js.Promise.then_(
             (
               result: (
                 Mutation.executionVariantResult(RegisterUserMutation.t),
                 Mutation.executionResult(RegisterUserMutation.t),
               ),
             ) => {
             switch (fst(result)) {
             | Data(data) =>
               Js.log2("The data from the registration mutation is", data);
               switch (data##register) {
               | Some(u) =>
                 Storage.saveUserToStorage({
                   name: u##username,
                   userId: u##user_id,
                   uuid: user.uuid,
                 });
                 AccessToken.setAccessToken(u##token);
               | None => ShowError |> dispatch
               };

               CompleteRegistration |> dispatch;
             | _ => ShowError |> dispatch
             };
             Js.Promise.resolve();
           })
        |> Js.Promise.catch(error => {
             Js.log2("Something wrong", error);
             Js.Promise.resolve();
           })
        |> ignore;
      | _ => ()
      };

      None;
    },
    [|state|],
  );

  <div className="w-screen h-screen flex justify-center items-center">
    {switch (state) {
     | Loading => S.str("Please wait while loading data")
     | LoggingIn(user)
     | Registering(user) =>
       S.str("Please wait while registering you (" ++ user.name ++ ")")
     | CreatingUser =>
       <Login onSubmitName={name => CreateUser(name) |> dispatch} />
     | Error => S.str("Oops something went wrong, sorry :(")
     | LoggedIn(user) => <GamesManager user />
     }}
  </div>;
};

let default = make;