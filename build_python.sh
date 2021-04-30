# build python

cd /tmp

# same version should be installed somewhere (PYTHONHOME?)
git clone --depth 1 --branch v3.8.5 https://github.com/python/cpython

cd cpython

echo "*static*
math mathmodule.c _math.c" > Modules/Setup.local
# check Modules/Setup if anything missing

# on MAC
sudo xcode-select --install
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install git openssl readline
export PKG_CONFIG_PATH="$(brew --prefix openssl)/lib/pkgconfig"
export CPPFLAGS="-I$(brew --prefix readline)/include"
export LDFLAGS="-L$(brew --prefix readline)/lib"

# all
./configure --disable-shared
make -j

# ./libpython3.8.a is ready
