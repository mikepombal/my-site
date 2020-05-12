open MemoState;

[@react.component]
let make = (~size, ~width=0, ~height=0, ~cards, ~chooseCard) => {
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
                  let card = ListLabels.nth(cards, x);
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
       </div>

     | _ => ReasonReact.null
     }}
  </div>;
};

let default = make;