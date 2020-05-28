require("dotenv").config();

const withTM = require("next-transpile-modules")([
  "bs-platform",
  "reason-apollo-hooks",
]);

module.exports = withTM({
  pageExtensions: ["jsx", "js", "bs.js"],
  env: {
    analytics: process.env.GA_ID,
    SERVER_URL: process.env.SERVER_URL,
    X_HASURA_ADMIN_SECRET: process.env.X_HASURA_ADMIN_SECRET,
  },
});
