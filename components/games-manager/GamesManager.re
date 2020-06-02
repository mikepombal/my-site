open Types;

[@react.component]
let make = (~user) => {
  S.str("Welcome " ++ user.name ++ " to the games management section");
};

let default = make;