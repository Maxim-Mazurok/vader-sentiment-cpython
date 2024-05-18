const { Worker } = require("worker_threads");
const text = process.argv[2] || "Woohooo 😍 ✌️";
let i = 0;

function runService(workerData) {
  return new Promise((resolve, reject) => {
    const worker = new Worker("./worker-worker.js", { workerData });
    worker.on("message", resolve);
    worker.on("error", reject);
    worker.on("exit", (code) => {
      if (code !== 0) {
        reject(new Error(`Worker stopped with exit code ${code}`));
      }
    });
  });
}

const startDateTime = new Date();

const next = async () => {
  try {
    console.log(`calling with "${text}"`);
    const result = await runService(text);
    i++;
    const iterationsPerSecond = i / ((new Date() - startDateTime) / 1000);
    console.log({ result, i, iterationsPerSecond });
  } catch (err) {
    console.error(err);
  }
  // global.gc();
  next();
};

next();
