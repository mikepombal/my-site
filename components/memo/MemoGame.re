open MemoState;

[@react.component]
let make = (~level=1) => {
  let initialState = React.useMemo1(() => initialState(level), [|level|]);
  let (state, dispatch) = React.useReducer(reducer, initialState);
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

  <div className="relative p-1 md:p-2 xl:p-4">
    <div
      className="bg-blue-500 text-white text-4xl font-extrabold flex justify-center items-center p-3 mb-3 rounded-lg">
      {ReasonReact.string("Memo")}
    </div>
    <div className="
        flex flex-col lg:flex-row
        ">
      <div className="flex justify-center items-center lg:pr-2 mb-4 lg:w-1/6">
        <div
          className="
            bg-gray-100 w-full flex items-center flex-row items-stretch rounded-lg shadow-lg overflow-hidden
            lg:flex-col lg:pb-4 lg:justify-center
            ">
          <div
            className="
                bg-purple-500 text-white text-xl py-2 shadow-md flex-grow flex justify-center items-baseline
                lg:w-full lg:text-3xl
            ">
            {ReasonReact.string(
               "Level " ++ string_of_int(state.currentLevel.number) ++ " / 7",
             )}
          </div>
          <div
            className="flex-grow flex justify-center items-center lg:flex-col">
            <div
              className="
            text-xl text-gray-500
            lg:text-2xl lg:mt-6
            ">
              {ReasonReact.string("Lives:")}
            </div>
            <div
              className="
            text-2xl text-gray-700 pl-2
            lg:text-6xl
            ">
              {ReasonReact.string(string_of_int(state.livesLeft))}
            </div>
          </div>
        </div>
      </div>
      <div className="flex-grow pl-2 lg:pl-4">
        <div
          style={ReactDOMRe.Style.make(
            ~maxWidth=
              string_of_int(
                state.currentLevel.cols * 90 / state.currentLevel.rows,
              )
              ++ "vh",
            (),
          )}>
          <BoardCards
            level={state.currentLevel}
            cards={state.cards}
            chooseCard
          />
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
             className="bg-gray-400 rounded-lg flex justify-center items-center flex-col py-10 px-10 bg-opacity-75 lg:px-20">
             <div
               className="text-gray-700 text-4xl mb-8 text-center lg:text-6xl">
               {ReasonReact.string(
                  switch (state.status, state.currentLevel.number) {
                  | (GameWon, 7) => "Champion! You've beaten all the levels."
                  | (GameWon, _) => "Winner!"
                  | (GameLost, _) => "Unlucky :("
                  | (_, _) => ""
                  },
                )}
             </div>
             <div className="flex">
               <button
                 onClick=onClickRestartLevel
                 className="block bg-blue-700 text-white text-lg px-6 py-3 rounded shadow">
                 {ReasonReact.string("Restart")}
               </button>
               {state.status == GameWon
                && state.currentLevel.number < ListLabels.length(levels)
                  ? <button
                      onClick=onClickNextLevel
                      className="block bg-blue-700 text-white text-lg px-6 py-3 rounded shadow ml-8">
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