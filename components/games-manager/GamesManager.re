open Types;

type state =
  | Home
  | NewGame;

type action =
  | StartNewGame
  | BackHome;

let reducer = (state, action) => {
  switch (state, action) {
  | (Home, StartNewGame) => NewGame
  | (NewGame, BackHome) => Home
  | (_, _) => NewGame
  };
};

[@react.component]
let make = (~user) => {
  let (state, dispatch) = React.useReducer(reducer, Home);

  switch (state) {
  | Home =>
    <div className="flex flex-col">
      {S.str("Welcome " ++ user.name ++ " to the games management section")}
      <button
        className="bg-blue-400 text-white"
        onClick={_event => StartNewGame |> dispatch}>
        {S.str("Start New Game")}
      </button>
    </div>
  | NewGame => <NewGame goBackHome={_event => BackHome |> dispatch} />
  };
};

let default = make;