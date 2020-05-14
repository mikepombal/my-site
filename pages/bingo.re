type num = {
  value: int,
  chosen: bool,
};

type state = {
  grid: array(num),
  selectedNumber: array(int),
  variant: int,
};

type action =
  | Choose(int);

let prepareNewGame = variant => {
  variant: 3,
  grid: Array.map(i => {value: i, chosen: false}, Belt.Array.range(1, 50)),
  selectedNumber:
    Belt.Array.makeByAndShuffle(50, i => i + 1)
    |> Belt.Array.slice(~len=variant * variant, ~offset=0),
};

let initialiseState = () => prepareNewGame(3);

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
  <div className="p-10">
    <div
      className="text-5xl bg-purple-700 text-white flex justify-center items-center rounded-lg">
      {ReasonReact.string("Bingo")}
    </div>
    <div className="grid grid-cols-3 gap-10 mt-10">
      <div className="grid grid-cols-3 gap-2">
        {ReasonReact.array(
           Array.map(
             x =>
               <div
                 key={"selected" ++ string_of_int(x)}
                 className={
                   "flex justify-center items-center p-6 text-4xl border-2 rounded-lg"
                   ++ " "
                   ++ (
                     state.grid[x - 1].chosen
                       ? "bg-green-300 border-green-300 text-white"
                       : "text-purple-700 border-purple-300"
                   )
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
                   "flex justify-center items-center p-6 text-xl border-2  cursor-pointer rounded-lg"
                   ++ " "
                   ++ (
                     x.chosen
                       ? "bg-red-300 border-red-300 text-white"
                       : "border-purple-200 text-purple-700"
                   )
                 }
                 onClick={_event => dispatch(Choose(x.value))}>
                 {ReasonReact.string(string_of_int(x.value))}
               </div>,
             state.grid,
           ),
         )}
      </div>
    </div>
  </div>;
};

let default = make;