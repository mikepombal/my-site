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
    ACTION_SECRET_ENV: process.env.ACTION_SECRET_ENV,
    JWT_SECRET_KEY: process.env.JWT_SECRET_KEY,
    JWT_SECRET_TYPE: process.env.JWT_SECRET_TYPE,
    JWT_TOKEN_EXPIRES: process.env.JWT_TOKEN_EXPIRES,
  },
});
