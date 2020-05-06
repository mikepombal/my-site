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
          Js.Global.setTimeout(() => dispatch(HideSelectedCards), 2000);
        ();
      };
      None;
    },
    [|state.status|],
  );

  <div className="flex w-full h-screen items-center justify-center">
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
  </div>;
};

let default = make;