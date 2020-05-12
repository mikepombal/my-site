open MemoState;

[@react.component]
let make = (~size=6, ~width=0, ~height=0) => {
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

  <div className="w-full pb-75pc relative">
    {switch (width, height) {
     | (w, h) when w > 0 && h > 0 =>
       <div className="absolute inset-0 flex justify-center items-center">
         <div className="
        grid grid-cols-4 gap-5
    ">
           {ReasonReact.array(
              Array.map(
                x => {
                  let card = ListLabels.nth(state.cards, x);
                  <Card
                    key={"card-" ++ string_of_int(x)}
                    num=x
                    length={string_of_int(w / 5) ++ "px"}
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
       </div>

     | _ => ReasonReact.null
     }}
  </div>;
};

let default = make;