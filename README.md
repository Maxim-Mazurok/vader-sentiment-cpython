# vader-sentiment-cpython

Updated replacement for [vader-sentiment](https://www.npmjs.com/package/vader-sentiment) ([vaderSentiment-js](https://github.com/vaderSentiment/vaderSentiment-js)) that runs original [vaderSentiment](https://github.com/cjhutto/vaderSentiment) natively, using CPython.

## Motivation

[vader-sentiment](https://www.npmjs.com/package/vader-sentiment) is outdated and doesn't support emoji - vital element of comments nowadays.

## Getting Started for dev

1. Run `npm ci`
1. Install dependencies. On Ubuntu, run [`./deps.sh`](./deps.sh)
1. Build python and boost statically (see [`build_boost.sh`](./build_boost.sh) and [`build_python.sh`](./build_python.sh))
1. Generate prebuild: `npm run prebuild` (might need to update hardcoded libs)
1. Run it: `node test.js "your awesome text goes here"`

## Getting Started for end user

Note: target machine should have same python (and glibc?) version, as dev machine

Note: currently is was tested on Ubuntu 20, and on Heroku (with Ubuntu 20). Check `mac` branch for Mac OS

Note: if you'd like to use it on another linux distro, at least install Python 3.8.5 and make sure that `python3` points to it

Note: requires Python 3.8.5 (installed on Ubuntu 20 by default)

1. Run `npm install Maxim-Mazurok/vader-sentiment-cpython`
2. Add [`install_vader.sh`](./install_vader.sh) script to your project, and run it before using module.
   You can include it in `start` script, like so: `"start": "bash ./install_vader.sh && node start.js",`
