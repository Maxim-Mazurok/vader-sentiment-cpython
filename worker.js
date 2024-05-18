const { parentPort, workerData } = require("worker_threads");
const vader = require("./index");

parentPort.postMessage(vader(workerData));
