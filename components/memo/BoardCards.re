open MemoState;

[@react.component]
let make = (~level, ~cards, ~chooseCard) => {
  let cssGridCol =
    switch (level.cols) {
    | 4 => " md:grid-cols-4"
    | 5 => " md:grid-cols-5"
    | 6 => " md:grid-cols-6"
    | _ => ""
    };
  <div className="w-full">
    <div
      className={
        "grid grid-cols-3 gap-4 md:gap-6 xl:gap-8" ++ " " ++ cssGridCol
      }>
      {ReasonReact.array(
         Array.map(
           x => {
             let card = ListLabels.nth(cards, x);
             <Card
               key={"card-" ++ string_of_int(x)}
               num=x
               show={card.show}
               img={card.image}
               chooseCard
             />;
           },
           Array.of_list(ListUtils.range(0, level.size - 1)),
         ),
       )}
    </div>
  </div>;
};

let default = make;