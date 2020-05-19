let initGA = () => ReactGA.initialize(Process.envAnalytics);

let logPageView = pathname => {
  ReactGA.set({"page": pathname});
  ReactGA.pageview(pathname);
};

let logEvent = (~category, ~action) =>
  ReactGA.event({"category": category, "action": action});