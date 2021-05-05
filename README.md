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
   You can include it in `start` script, like so: `"start": "bash ./node_modules/vader-sentiment-cpython/install_vader.sh && node start.js",`

## Current stage

It only has prebuild for Ubuntu 20 and Python 3.8.5.

I have to figure out how to make it more portable and independent from installed Python interpreter.

As far as I understand, I have to create portable Python interpreter, similar to how [pyinstaller](https://github.com/pyinstaller/pyinstaller) works.

### How pyinstaller embeds python?

Disclaimer: this is my (very limited) understanding.

- It bundles copy of the system (`libpython3.8.so.1.0` in my case)
- It doesn't bundle system Python interpreter executable. Instead, it builds own Python interpreter (kind of), which is embedded in the final binary executable.
- I think they use `objcopy` on Linux to bundle archives into one binary, see [api.py#L645](https://github.com/pyinstaller/pyinstaller/blob/532a465e348f84e1839526fa39bcc8d4155a2912/PyInstaller/building/api.py#L645)
- Python "starts" in [`pyi_pylib_start_python` function](https://github.com/pyinstaller/pyinstaller/blob/ed4bf7406bae5a6c070079b6c4b3160e740a546f/bootloader/src/pyi_pythonlib.c#L385)
- [pyinstaller bootloader's entrypoint](https://github.com/pyinstaller/pyinstaller/blob/ed4bf7406bae5a6c070079b6c4b3160e740a546f/bootloader/src/main.c#L89) is based on an [Python 2](https://github.com/python/cpython/blob/8d21aa21f2cbc6d50aab3f420bb23be1d081dac4/Modules/python.c) version of [Python interpreter main program](https://github.com/python/cpython/blob/96d5c7038b06e93d20822d28ed42a2183f876857/Modules/main.c)

So... Looks like I have to reuse pyinstaller's bootloader in order to create portable python interpreter that I can ship with this package.
But instead of running in console mode (and requiring to be ran using `spawn child process`), it'll be possible to embed NAPI into it, so it'll be a NodeJS package.
