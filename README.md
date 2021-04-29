# vader-sentiment-cpython

Updated replacement for [vader-sentiment](https://www.npmjs.com/package/vader-sentiment) ([vaderSentiment-js](https://github.com/vaderSentiment/vaderSentiment-js)) that runs original [vaderSentiment](https://github.com/cjhutto/vaderSentiment) natively, using CPython.

## Motivation

[vader-sentiment](https://www.npmjs.com/package/vader-sentiment) is outdated and doesn't support emoji - vital element of comments nowadays.

## Getting Started for dev

1. Install dependencies. On Ubuntu, run [`./deps.sh`](./deps.sh)
1. Build python and boost statically (see [`build_boost.sh`](./build_boost.sh) and [`build_python.sh`](./build_python.sh))
1. Generate prebuild: `npm run prebuild` (might need to update hardcoded libs)
1. Run it: `node test.js "your awesome text goes here"`

## Getting Started for end user

Note: target machine should have same glibc as dev machine

1. Follow [dev guide](#getting-started-for-dev)
1. Copy [`prebuild`](./prebuild) folder and [`test.js`](./test.js) to your target machine
1. Run [`install_vader.sh`](./install_vader.sh) in your target machine
1. Run it: `node test.js "your awesome text goes here"`
