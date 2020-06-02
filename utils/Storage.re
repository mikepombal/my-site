open Dom.Storage;
open Types;

let saveUserToStorage = user => {
  localStorage |> setItem("name", user.name);
  localStorage |> setItem("uuid", user.uuid);
  localStorage |> setItem("userId", user.userId |> string_of_int);
  ();
};

let getUserFromStorage = () => {
  let m_name = localStorage |> getItem("name");
  let m_uuid = localStorage |> getItem("uuid");
  let m_userId = localStorage |> getItem("userId");
  switch (m_name, m_uuid, m_userId) {
  | (Some(name), Some(uuid), Some(userId)) =>
    Some({name, uuid, userId: userId |> int_of_string})
  | _ => None
  };
};