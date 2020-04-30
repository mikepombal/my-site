module Card = {
  [@react.component]
  let make = () =>
    <div
      className="
        bg-endless-clouds border border-gray-300 rounded-lg w-24 h-24 bg-white flex justify-center items-center shadow
      "
    />;
};

[@react.component]
let make = () => {
  <div className="flex w-full h-screen items-center justify-center">
    <div className="grid grid-cols-3 gap-4">
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