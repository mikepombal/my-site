open Dom.Storage;
open Types;

let saveUserToStorage = (name, uuid) => {
  localStorage |> setItem("name", name);
  localStorage |> setItem("uuid", uuid);
  ();
};

let getUserFromStorage = () => {
  let name = localStorage |> getItem("name");
  let uuid = localStorage |> getItem("uuid");
  switch (name, uuid) {
  | (Some(n), Some(u)) => Some({name: n, uuid: u})
  | _ => None
  };
};