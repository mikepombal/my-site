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

  <div
    className=" m-auto relative"
    style={ReactDOMRe.Style.make(~maxWidth="133vh", ())}>
    <WithDimensions
      renderView={(width, height) =>
        <BoardCards size width height cards={state.cards} chooseCard />
      }
    />
    {state.status == EndGame
       ? <div
           className="bg-gray-400 bg-opacity-50 absolute inset-0 rounded-lg flex justify-center items-center">
           <Animation.Div
             exit={"scale": 0.0}
             initial={"scale": 0.0}
             animate={"scale": 1.0}
             transition={"delay": 0.3}
             className="bg-gray-400 rounded-lg flex justify-center items-center flex-col py-10 px-20 bg-opacity-75">
             <div className="text-gray-700 text-6xl mb-8">
               {ReasonReact.string("Winner!")}
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