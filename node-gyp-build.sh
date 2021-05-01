SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cd ${SCRIPT_DIR}

if npm run node-gyp-build-test; then
    echo "using prebuild"
else
    # only works for Python 3.8.5 for now
    echo "no prebuild, rebuilding..."
    bash ./build_boost.sh && bash ./build_python.sh
fi

npm run node-gyp-build
