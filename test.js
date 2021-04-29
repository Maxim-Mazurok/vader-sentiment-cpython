const bindingPath = require.resolve(`./prebuilds/linux-x64/node.napi.node`);
const binding = require(bindingPath);
console.log("binding() =", binding.hello());
