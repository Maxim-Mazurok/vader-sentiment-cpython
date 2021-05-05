# all of the following needs to be run on every machine before using module:
rm -f master.zip
wget https://github.com/cjhutto/vaderSentiment/archive/master.zip

rm -rf vaderSentiment-master
unzip master.zip

rm -f master.zip

# temp workaround
rm -rf $(dirname "$(which node)")/vaderSentiment-master
mv vaderSentiment-master $(dirname "$(which node)")/
