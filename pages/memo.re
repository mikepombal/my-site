[@react.component]
let make = () =>
  <WithDimensions
    renderView={(width, height) => <MemoGame size=12 width height />}
  />;

let default = make;