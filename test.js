const vader = require("./index");
const text = process.argv[2] || "Woohooo 😍 ✌️";

let i = 0;
const startDateTime = new Date();

while (true) {
  i++;
  const result = vader(text);
  if (i % 10_000 === 0) {
    const iterationsPerSecond = i / ((new Date() - startDateTime) / 1000);
    console.log({ result, i, iterationsPerSecond });
  }
}
