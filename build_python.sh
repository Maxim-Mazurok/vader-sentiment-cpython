# build python

cd /tmp

rm -rf /tmp/cpython

git clone --depth 1 --branch v3.8.5 https://github.com/python/cpython

cd cpython

echo "*static*
math mathmodule.c _math.c" > Modules/Setup.local
# check Modules/Setup if anything missing

# on MAC
if [ "$(uname)" == "Darwin" ]; then
    sudo xcode-select --install
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    brew install git openssl readline
    export PKG_CONFIG_PATH="$(brew --prefix openssl)/lib/pkgconfig"
    export CPPFLAGS="-I$(brew --prefix readline)/include"
    export LDFLAGS="-L$(brew --prefix readline)/lib"
elif [[ "$(uname)" == "Linux" ]]; then
    export CFLAGS="-fPIC"
    export LDFLAGS="-static"
    export LINKFORSHARED=" "
fi

./configure --disable-shared

if [[ -z "${DYNO}" ]]; then
  # looks like we're in heroku which can't handle stuff on free tire
  make
else
  make -j
fi

# ./libpython3.8.a is ready
