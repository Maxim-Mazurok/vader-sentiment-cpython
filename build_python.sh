# On Ubuntu, install OpenSSL (https://stackoverflow.com/a/57586800/4536543)
sudo apt-get install build-essential checkinstall libreadline-gplv2-dev libncursesw5-dev libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev

cd /tmp
curl https://www.openssl.org/source/openssl-1.0.2o.tar.gz | tar xz
cd openssl-1.0.2o
./config shared
./Configure darwin64-x86_64-cc -shared # on mac
make -j

mkdir lib
cp ./*.{so,so.1.0.0,a,pc} ./lib

# build python

cd /tmp

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

# Ubuntu
./configure LDFLAGS="-static" --with-openssl=/Users/max/Downloads/openssl-1.0.2o --disable-shared
make LDFLAGS="-static" LINKFORSHARED=" " -j

# Mac
./configure --disable-shared
make LINKFORSHARED=" " -j

# ./libpython3.8.a is ready