[@react.component]
let make = () =>
  <div
    className=" m-auto" style={ReactDOMRe.Style.make(~maxWidth="133vh", ())}>
    <WithDimensions
      renderView={(width, height) => <MemoGame size=12 width height />}
    />
  </div>;

let default = make;