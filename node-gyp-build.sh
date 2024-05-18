SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd ${SCRIPT_DIR}

if npm run node-gyp-build-test; then
    echo "using prebuild"
elif [ "$(python3 -V)" == "Python 3.8.5" ]; then
    # only works for Python 3.8.5 for now
    echo "no prebuild, rebuilding..."
    bash ./build_boost.sh && bash ./build_python.sh
else
    echo "no prebuild, no Python 3.8.5, can't rebuild... make sure that `python3 -V` returns 'Python 3.8.5'"
    exit 1
fi

npm run node-gyp-build
