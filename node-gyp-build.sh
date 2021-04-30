# only on heroku for now
if [[ "${HEROKU_ENV}" ]]; then

    node-gyp-build

fi