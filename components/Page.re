[@react.component]
let make = (~children) => {
  React.useEffect1(
    () => {
      Js.log(Global.pathname);
      ReactGA.initialize(Process.envAnalytics);
      ReactGA.set({"page": Global.pathname});
      ReactGA.pageview(Global.pathname);
      None;
    },
    [||],
  );
  <>
    <Next.Head>
      <meta
        name="viewport"
        content="width=device-width, initial-scale=1, shrink-to-fit=no, viewport-fit=cover"
      />
      <title> {React.string("MM")} </title>
    </Next.Head>
    children
  </>;
};