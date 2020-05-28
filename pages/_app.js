import "../styles/global.css";
import App from "next/app";
import { make as Page } from "../components/Page.bs";
import { withApollo } from "../utils/withApollo";
import { ApolloProvider } from "@apollo/react-common";

class MySiteApp extends App {
  static async getInitialProps({ Component, ctx }) {
    let pageProps = {};

    if (Component.getInitialProps) {
      pageProps = await Component.getInitialProps(ctx);
    }
    return { pageProps };
  }

  render() {
    const { Component, pageProps, apolloClient } = this.props;

    return (
      <ApolloProvider client={apolloClient}>
        <Page>
          <Component {...pageProps} />
        </Page>
      </ApolloProvider>
    );
  }
}

export default withApollo(MySiteApp);
