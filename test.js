const nativeAddonPath = require.resolve(`./prebuilds/linux-x64/node.napi.node`);
const nativeAddon = require(nativeAddonPath);
const text = process.argv[2] || "Woohooo 😍 ✌️";
console.log(`nativeAddon( ${text} ) = ${nativeAddon(text)}`);
