# only on heroku for now
if [[ "${HEROKU_ENV}" ]]; then

    ./node_modules/.bin/node-gyp-build

fi
