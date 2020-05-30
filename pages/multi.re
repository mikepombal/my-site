open Types;
open ApolloHooks;

let getOrDefault = uuid => uuid->Js.Json.decodeString->Belt.Option.getExn;

module RegisterUserMutation = [%graphql
  {|
    mutation upsert_user ($id: uuid!, $username: String!) {
        insert_users_one(object: { id: $id, username: $username }, on_conflict: {constraint: users_pkey, update_columns: [last_seen]}) {
            id @bsDecoder(fn: "getOrDefault")
            username
            last_seen
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
    RegisteringUser({name, uuid: Uuid.generateUUID()})
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
        Js.log("Sending request!");
        let variables =
          RegisterUserMutation.make(
            ~id=Js.Json.string(user.uuid),
            ~username=user.name,
            (),
          )##variables;
        register(~variables, ())
        |> Js.Promise.then_(_ => {
             CompleteRegistration |> dispatch;
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
     | LoggedIn(user) =>
       S.str("Welcome back " ++ user.name ++ "(" ++ user.uuid ++ ")")
     | CreatingUser =>
       <Login onSubmitName={name => CreateUser(name) |> dispatch} />
     | Error => S.str("Oops something went wrong, sorry :(")
     }}
  </div>;
};

let default = make;