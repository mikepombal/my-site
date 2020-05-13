type num = {
  value: int,
  chosen: bool,
};

type state = {
  grid: array(num),
  selectedNumber: array(int),
};

type action =
  | Choose(int);

let initialiseState = () => {
  grid: Array.map(i => {value: i, chosen: false}, Belt.Array.range(1, 50)),
  selectedNumber:
    Belt.Array.makeByAndShuffle(50, i => i + 1)
    |> Belt.Array.slice(~len=9, ~offset=0),
};

let reducer = (state, action) => {
  switch (action) {
  | Choose(num) => {
      ...state,
      grid:
        Array.map(
          i => {...i, chosen: i.value == num ? true : i.chosen},
          state.grid,
        ),
    }
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialiseState());
  <div className="grid grid-cols-3 gap-10 m-10">
    <div className="grid grid-cols-3 gap-2">
      {ReasonReact.array(
         Array.map(
           x =>
             <div
               key={"selected" ++ string_of_int(x)}
               className={
                 "flex justify-center items-center p-6 text-gray-800 text-4xl border-2 border-gray-400"
                 ++ (state.grid[x - 1].chosen ? " bg-green-300" : "")
               }>
               {ReasonReact.string(string_of_int(x))}
             </div>,
           state.selectedNumber,
         ),
       )}
    </div>
    <div className="grid grid-cols-10 gap-2 col-span-2">
      {ReasonReact.array(
         Array.map(
           x =>
             <div
               key={"grid" ++ string_of_int(x.value)}
               className={
                 "flex justify-center items-center p-6 text-gray-800 text-xl border-2 border-gray-400 cursor-pointer"
                 ++ (x.chosen ? " bg-red-300" : "")
               }
               onClick={_event => dispatch(Choose(x.value))}>
               {ReasonReact.string(string_of_int(x.value))}
             </div>,
           state.grid,
         ),
       )}
    </div>
  </div>;
};

let default = make;