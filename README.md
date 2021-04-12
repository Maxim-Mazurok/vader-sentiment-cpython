# vader-sentiment-cpython

Updated replacement for [vader-sentiment](https://www.npmjs.com/package/vader-sentiment) ([vaderSentiment-js](https://github.com/vaderSentiment/vaderSentiment-js)) that runs original [vaderSentiment](https://github.com/cjhutto/vaderSentiment) natively, using CPython.

## Motivation

[vader-sentiment](https://www.npmjs.com/package/vader-sentiment) is outdated and doesn't support emoji - vital element of comments nowadays.

## Getting Started

1. Install dependencies. On Ubuntu, run `./deps.sh`
1. Build binary: `node-gyp configure && node-gyp build` (might need to update hardcoded libs)
1. Run it: `npm start` (uses hardcoded string for now, in c++ code)
