[@react.component]
let make = (~img, ~num, ~show, ~chooseCard, ~length) => {
  let onClick = React.useCallback1(_event => chooseCard(num), [||]);
  <div
    className="
        border border-gray-300 rounded-lg bg-white flex justify-center items-center shadow overflow-hidden
      "
    style={ReactDOMRe.Style.make(~width=length, ~height=length, ())}>
    {show
       ? <div
           className="
            bg-gray-100 w-full h-full flex justify-center items-center text-gray-800 p-6
        ">
           <img src=img alt={"image " ++ string_of_int(num)} />
         </div>
       : <div
           onClick
           className="
            bg-endless-clouds w-full h-full
        "
         />}
  </div>;
};

let default = make;