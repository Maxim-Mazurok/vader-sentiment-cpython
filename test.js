const nativeAddon = require("./index");
const text = process.argv[2] || "Woohooo 😍 ✌️";
console.log(`nativeAddon( ${text} ) = ${nativeAddon(text)}`);
