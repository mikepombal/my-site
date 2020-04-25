const Page = require("../components/Page.bs").make;

export default function App({ Component, pageProps }) {
  return (
    <Page>
      <Component {...pageProps} />
    </Page>
  );
}
