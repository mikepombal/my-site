[@react.component]
let make = (~img, ~num, ~show, ~chooseCard, ~length) => {
  let onClick = React.useCallback1(_event => chooseCard(num), [||]);
  <div
    style={ReactDOMRe.Style.make(
      ~width=string_of_int(length) ++ "px",
      ~height=string_of_int(length) ++ "px",
      ~padding="6%",
      (),
    )}>
    <div
      className="
        border border-gray-300 rounded-lg bg-white flex justify-center items-center shadow overflow-hidden w-full h-full
      ">
      {show
         ? <Animation.Div
             exit={"scale": 0.0}
             initial={"scale": 0.0}
             animate={"scale": 1.0}
             className="
            bg-gray-100 w-full h-full flex justify-center items-center text-gray-800 p-10pc
        ">
             <img src=img alt={"image " ++ string_of_int(num)} />
           </Animation.Div>
         : <div
             onClick
             className="
            bg-endless-clouds w-full h-full
        "
           />}
    </div>
  </div>;
};

let default = make;