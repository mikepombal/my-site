require("dotenv").config();

const withTM = require("next-transpile-modules")([
  "bs-platform",
  "reason-apollo-hooks",
]);

module.exports = withTM({
  pageExtensions: ["jsx", "js", "bs.js"],
  env: {
    analytics: process.env.GA_ID,
    GRAPHQL_SERVER_HTTPS: process.env.GRAPHQL_SERVER_HTTPS,
    GRAPHQL_SERVER_WS: process.env.GRAPHQL_SERVER_WS,
    X_HASURA_ADMIN_SECRET: process.env.X_HASURA_ADMIN_SECRET,
  },
});
