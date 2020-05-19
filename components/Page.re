[@react.component]
let make = (~children) => {
  React.useEffect1(
    () => {
      Analytics.initGA();
      Analytics.logPageView(Global.pathname);
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