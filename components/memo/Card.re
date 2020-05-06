[@react.component]
let make = (~img, ~num, ~show, ~chooseCard) => {
  let onClick = React.useCallback1(_event => chooseCard(num), [||]);
  <div
    className="
        border border-gray-300 rounded-lg w-24 h-24 bg-white flex justify-center items-center shadow overflow-hidden
        sm:w-32 sm:h-32
        md:w-40 md:h-40
        lg:w-48 lg:h-48
      ">
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