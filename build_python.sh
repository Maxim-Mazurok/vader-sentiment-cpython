# build python

git clone --depth 1 --branch v3.8.5 https://github.com/python/cpython

echo "*static*
math mathmodule.c _math.c" > Modules/Setup.local
# check Modules/Setup if anything missing

./configure --disable-shared

make -j

# ./libpython3.8.a is ready
