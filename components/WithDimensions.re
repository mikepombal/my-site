// import React, { useRef, useLayoutEffect, useState } from "react";

type dimension = {
  width: int,
  height: int,
};

let resetTimeout = 100;

[@react.component]
let make = (~renderView: (int, int) => ReasonReact.reactElement) => {
  let targetRef = React.useRef(Js.Nullable.null);
  let (dimensions, setDimensions) =
    React.useState(_ => {width: 0, height: 0});

  let getNewDimensions = () => {
    switch (React.Ref.current(targetRef)->Js.Nullable.toOption) {
    | Some(e) =>
      let element = ReactDOMRe.domElementToObj(e);
      setDimensions(_ =>
        {width: element##offsetWidth, height: element##offsetHeight}
      );
    | None => ()
    };
  };
  React.useEffect1(
    () => {
      getNewDimensions();
      let timer: ref(option(Js.Global.timeoutId)) = ref(None);
      let onResize = _ => {
        getNewDimensions();
      };
      Webapi.Dom.Window.addEventListener(
        "resize",
        _ => {
          switch (timer^) {
          | Some(timerId) => Js.Global.clearTimeout(timerId)
          | None => ()
          };
          timer := Some(Js.Global.setTimeout(_ => onResize(), 500));
          ();
        },
        Webapi.Dom.window,
      );
      Some(
        () =>
          Webapi.Dom.Window.removeEventListener(
            "resize",
            onResize,
            Webapi.Dom.window,
          ),
      );
    },
    [||],
  );
  <div ref={ReactDOMRe.Ref.domRef(targetRef)}>
    {renderView(dimensions.width, dimensions.height)}
  </div>;
};

let default = make;