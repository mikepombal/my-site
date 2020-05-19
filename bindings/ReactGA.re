type t;
type dimension = {. "page": string};
type event = {
  .
  "category": string,
  "action": string,
};

[@bs.module "react-ga"] external initialize: string => unit = "initialize";

[@bs.module "react-ga"] external set: dimension => unit = "set";

[@bs.module "react-ga"] external pageview: string => unit = "pageview";

[@bs.module "react-ga"] external event: event => unit = "event";