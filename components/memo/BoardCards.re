open MemoState;

[@react.component]
let make = (~level, ~width=0, ~height=0, ~cards, ~chooseCard) => {
  <div
    className="w-full relative"
    style={ReactDOMRe.Style.make(
      ~paddingBottom=string_of_int(level.rows * 100 / level.cols) ++ "%",
      (),
    )}>
    {switch (width, height) {
     | (w, h) when w > 0 && h > 0 =>
       <div className="absolute inset-0 flex justify-center items-center mx-4">
         <div
           style={ReactDOMRe.Style.make(
             ~gridTemplateColumns=
               "repeat(" ++ string_of_int(level.cols) ++ ", minmax(0, 1fr))",
             (),
           )}
           className="grid">
           {ReasonReact.array(
              Array.map(
                x => {
                  let card = ListLabels.nth(cards, x);
                  <Card
                    key={"card-" ++ string_of_int(x)}
                    num=x
                    length={w / level.cols}
                    show={card.show}
                    img={card.image}
                    chooseCard
                  />;
                },
                Array.of_list(ListUtils.range(0, level.size - 1)),
              ),
            )}
         </div>
       </div>

     | _ => ReasonReact.null
     }}
  </div>;
};

let default = make;