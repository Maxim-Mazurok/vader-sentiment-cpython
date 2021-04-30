# only on heroku for now
if [[ "${HEROKU_ENV}" ]]; then

    # build python

    git clone --depth 1 --branch v3.8.5 https://github.com/python/cpython

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
    fi

    # all
    ./configure --disable-shared

    make # add -j if not heroku

    # ./libpython3.8.a is ready

fi