open MemoState;

[@react.component]
let make = (~size=12) => {
  let (state, dispatch) = React.useReducer(reducer, initialState(size));
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
  let onClick = React.useCallback1(_event => dispatch(RestartGame), [||]);

  <div className="relative">
    <div
      className="grid grid-cols-6 m-auto px-4"
      style={ReactDOMRe.Style.make(~maxWidth="155vh", ())}>
      <div className="col-span-5">
        <WithDimensions
          renderView={(width, height) =>
            <BoardCards size width height cards={state.cards} chooseCard />
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
            {ReasonReact.string(string_of_int(state.lives))}
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
                  state.status == GameWon ? "Winner!" : "Loser!",
                )}
             </div>
             <button
               onClick
               className="block bg-blue-500 text-white text-lg p-3 rounded shadow">
               {ReasonReact.string("Restart")}
             </button>
           </Animation.Div>
         </div>
       : ReasonReact.null}
  </div>;
};

let default = make;