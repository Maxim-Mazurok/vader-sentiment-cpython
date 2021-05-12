import importlib
SentimentIntensityAnalyzer = getattr(importlib.import_module(
    "vaderSentiment-master.vaderSentiment.vaderSentiment"), "SentimentIntensityAnalyzer")


def print_sentiment_scores(sentence):
    analyser = SentimentIntensityAnalyzer()
    snt = analyser.polarity_scores(sentence)
    print(snt.get('compound'))


print_sentiment_scores("Woohooo 😍 ✌️")
