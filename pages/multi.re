open Types;
open ApolloHooks;

let getOrDefault = uuid => uuid->Js.Json.decodeString->Belt.Option.getExn;

module RegisterUserMutation = [%graphql
  {|
    mutation register($uuid: uuid!, $username: String!){
      register (uuid: $uuid, username: $username) {
        token
      }
    }
  |}
];

type state =
  | Loading
  | CreatingUser
  | RegisteringUser(user)
  | LoggedIn(user)
  | Error;

type action =
  | CreateUser(string)
  | LoadUser(option(user))
  | CompleteRegistration
  | ShowError;

let reducer = (state, action) =>
  switch (state, action) {
  | (Loading, LoadUser(Some(user))) => RegisteringUser(user)
  | (Loading, LoadUser(None)) => CreatingUser
  | (Loading, _) => state

  | (CreatingUser, CreateUser(name)) =>
    RegisteringUser({name, uuid: Uuid.generateUUID(), userId: (-1)})
  | (CreatingUser, _) => state

  | (RegisteringUser(user), CompleteRegistration) => LoggedIn(user)
  | (RegisteringUser(_), ShowError) => Error
  | (RegisteringUser(_), _) => state

  | (LoggedIn(_), _) => state

  | (Error, _) => state
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, Loading);
  let (register, _, _) = useMutation(RegisterUserMutation.definition);
  React.useEffect1(
    () => {
      switch (state) {
      | Loading => Storage.getUserFromStorage()->LoadUser |> dispatch
      | RegisteringUser(user) =>
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
               Js.log2("The data from the mutation is", data);
               //    switch (data##insert_users_one) {
               //    | Some(user) =>
               //      Storage.saveUserToStorage({
               //        name: user##username,
               //        uuid: user##token,
               //        userId: user##user_id,
               //      })
               //    | None => ShowError |> dispatch
               //    };

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
     | RegisteringUser(user) =>
       S.str("Please wait while registering you (" ++ user.name ++ ")")
     | CreatingUser =>
       <Login onSubmitName={name => CreateUser(name) |> dispatch} />
     | Error => S.str("Oops something went wrong, sorry :(")
     | LoggedIn(_user) => S.str("The login was succesfull")
     }}
  </div>;
};
// | LoggedIn(user) => <GamesManager user />

let default = make;