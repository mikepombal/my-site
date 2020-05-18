[@bs.val] external envAnalytics: option(string) = "process.env.analytics";
let envAnalytics = Belt.Option.getWithDefault(envAnalytics, "");