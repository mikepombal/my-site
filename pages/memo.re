module Card = {
  [@react.component]
  let make = (~show=true) =>
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
            bg-gray-100 w-full h-full flex justify-center items-center text-gray-800 p-2
        ">
             <img src="/undraw_aircraft_fbvl.svg" alt="my image" />
           </div>
         : <div
             className="
            bg-endless-clouds w-full h-full
        "
           />}
    </div>;
};

[@react.component]
let make = () => {
  <div className="flex w-full h-screen items-center justify-center">
    <div
      className="
        grid grid-cols-3 gap-4
        md:grid-cols-4
        xl:grid-cols-6
    ">
      {ReasonReact.array(
         Array.map(
           x => <Card key={"card-" ++ string_of_int(x)} />,
           Array.of_list(ListUtils.range(1, 12)),
         ),
       )}
    </div>
  </div>;
};

let default = make;