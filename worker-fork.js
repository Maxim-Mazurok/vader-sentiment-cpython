const vader = require("./index");

const workerData = process.argv[2];
const result = vader(workerData);

process.send(result);
process.exit(0);
