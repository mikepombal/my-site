const withTM = require("next-transpile-modules")(["bs-platform"]);

module.exports = withTM({
  pageExtensions: ["jsx", "js", "bs.js"],
  env: {
    analytics: "UA-166787685-1",
  },
});
