open MemoState;

[@react.component]
let make = (~size=6) => {
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

  <div className="flex w-full h-full items-center justify-center relative">
    <div
      className="
        grid grid-cols-3 gap-4
        md:grid-cols-4 gap-5
        xl:grid-cols-6
    ">
      {ReasonReact.array(
         Array.map(
           x => {
             let card = ListLabels.nth(state.cards, x);
             <Card
               key={"card-" ++ string_of_int(x)}
               num=x
               show={card.show}
               img={card.image}
               chooseCard
             />;
           },
           Array.of_list(ListUtils.range(0, size - 1)),
         ),
       )}
    </div>
    {state.status == EndGame
       ? <div
           className="bg-gray-400 bg-opacity-50 absolute inset-0 rounded-lg flex justify-center items-center flex-col">
           <div className="text-gray-800 text-6xl mb-8">
             {ReasonReact.string("Winner!")}
           </div>
           <button
             onClick
             className="block bg-blue-500 text-white text-lg p-3 rounded shadow">
             {ReasonReact.string("Restart")}
           </button>
         </div>
       : ReasonReact.null}
  </div>;
};

let default = make;