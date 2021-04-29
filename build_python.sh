# install OpenSSL (https://stackoverflow.com/a/57586800/4536543)
sudo apt-get install build-essential checkinstall libreadline-gplv2-dev libncursesw5-dev libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev

cd /usr/src
sudo curl https://www.openssl.org/source/openssl-1.0.2o.tar.gz | sudo tar xz
cd openssl-1.0.2o
sudo ./config shared --prefix=/usr/local/
sudo make
sudo make install

sudo mkdir lib
sudo cp ./*.{so,so.1.0.0,a,pc} ./lib

# build python

git clone --depth 1 --branch v3.8.5 https://github.com/python/cpython

echo "*static*
math mathmodule.c _math.c" > Modules/Setup.local
# check Modules/Setup if anything missing

./configure LDFLAGS="-static" --disable-shared --with-openssl=/usr/src/openssl-1.0.2o

make LDFLAGS="-static" LINKFORSHARED=" " -j

# ./libpython3.8.a is ready