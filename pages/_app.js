import "../styles/global.css";
import { make as Page } from "../components/Page.bs";

export default function App({ Component, pageProps }) {
  return (
    <Page>
      <Component {...pageProps} />
    </Page>
  );
}
