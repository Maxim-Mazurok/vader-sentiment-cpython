sudo apt-get install build-essential gdb
sudo apt install python3-pip python3-dev

rm -f master.zip
wget https://github.com/cjhutto/vaderSentiment/archive/master.zip

rm -rf vaderSentiment-master
unzip master.zip

rm -f master.zip

mv vaderSentiment-master $(dirname "$(which node)")/ # temp workaround