type props = {. "scale": float};
type transitionProps = {. "delay": float};

module Div = {
  [@react.component] [@bs.module "framer-motion"] [@bs.scope "motion"]
  external make:
    (
      ~children: React.element=?,
      ~exit: props=?,
      ~initial: props=?,
      ~animate: props=?,
      ~transition: transitionProps=?,
      ~className: string=?,
      ~onClick: ReactEvent.Mouse.t => unit=?
    ) =>
    React.element =
    "div";
};