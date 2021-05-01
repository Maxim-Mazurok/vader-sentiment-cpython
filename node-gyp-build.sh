# only on heroku for now
if [[ "${HEROKU_ENV}" ]]; then

    ls -la

    pwd

    SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

    echo ${SCRIPT_DIR}

    cd ${SCRIPT_DIR}

    npm run node-gyp-build

fi
