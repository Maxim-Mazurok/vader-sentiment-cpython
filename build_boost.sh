cd /tmp
wget https://sourceforge.net/projects/boost/files/boost/1.76.0/boost_1_76_0.tar.bz2
tar --bzip2 -xf boost_1_76_0.tar.bz2
cd boost_1_76_0/
./bootstrap.sh
./b2 cxxflags=-fPIC cflags=-fPIC -a link=static
