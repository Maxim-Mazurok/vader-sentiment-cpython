const vader = require("./index");
const text = process.argv[2] || "Woohooo 😍 ✌️";
console.log(`calling with "${text}"`);
console.log({ result: vader(text) });
