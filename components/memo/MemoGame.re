open MemoState;

[@react.component]
let make = (~level=1) => {
  let (state, dispatch) = React.useReducer(reducer, initialState(level));
  let chooseCard =
    React.useCallback1(num => dispatch(ChooseCard(num)), [||]);
  React.useEffect1(
    () => {
      if (state.status == TwoSelectedCards) {
        let _ =
          Js.Global.setTimeout(() => dispatch(HideSelectedCards), 1000);
        ();
      };
      None;
    },
    [|state.status|],
  );
  let onClickRestartLevel =
    React.useCallback1(
      _event => dispatch(SetNewGame(state.currentLevel.number)),
      [|state.currentLevel|],
    );
  let onClickNextLevel =
    React.useCallback1(
      _event => dispatch(SetNewGame(state.currentLevel.number + 1)),
      [|state.currentLevel|],
    );
  Js.log("Parent");

  <div className="relative">
    <div
      className="grid grid-cols-6 m-auto px-4"
      style={ReactDOMRe.Style.make(
        ~maxWidth=
          string_of_int(
            state.currentLevel.cols * 100 / state.currentLevel.rows * 7 / 6,
          )
          ++ "vh",
        (),
      )}>
      <div className="col-span-5">
        <WithDimensions
          unique={
            string_of_int(state.currentLevel.rows)
            ++ "x"
            ++ string_of_int(state.currentLevel.cols)
          }
          renderView={(width, height) =>
            <BoardCards
              level={state.currentLevel}
              width
              height
              cards={state.cards}
              chooseCard
            />
          }
        />
      </div>
      <div className=" flex justify-center items-center p-2">
        <div
          className="bg-gray-100 w-full flex justify-center items-center flex-col rounded-lg py-4 shadow-lg">
          <div className="text-2xl text-gray-500">
            {ReasonReact.string("Left")}
          </div>
          <div className="text-6xl text-gray-700">
            {ReasonReact.string(string_of_int(state.livesLeft))}
          </div>
        </div>
      </div>
    </div>
    {state.status == GameWon || state.status == GameLost
       ? <div
           className="bg-gray-400 bg-opacity-50 absolute inset-0 rounded-lg flex justify-center items-center">
           <Animation.Div
             exit={"scale": 0.0}
             initial={"scale": 0.0}
             animate={"scale": 1.0}
             transition={"delay": 0.3}
             className="bg-gray-400 rounded-lg flex justify-center items-center flex-col py-10 px-20 bg-opacity-75">
             <div className="text-gray-700 text-6xl mb-8">
               {ReasonReact.string(
                  state.status == GameWon ? "Winner!" : "Unlucky :(",
                )}
             </div>
             <div className="flex">
               <button
                 onClick=onClickRestartLevel
                 className="block bg-blue-700 text-white text-lg p-3 rounded shadow">
                 {ReasonReact.string("Restart")}
               </button>
               {state.status == GameWon
                && state.currentLevel.number < ListLabels.length(levels)
                  ? <button
                      onClick=onClickNextLevel
                      className="block bg-blue-700 text-white text-lg p-3 rounded shadow ml-8">
                      {ReasonReact.string("Next Level")}
                    </button>
                  : ReasonReact.null}
             </div>
           </Animation.Div>
         </div>
       : ReasonReact.null}
  </div>;
};

let default = make;