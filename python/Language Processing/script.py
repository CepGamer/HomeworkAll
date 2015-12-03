# coding=UTF-8

def parseData(filename):
	from re import sub
	f = open(filename, 'r').read().split('\n')
	posts = [0] * len(f)
	for i, string in enumerate(f):
		try:
			smile = sub('(:-*\)+)|(\)\)+)', 'smile.', string.split('\t')[3])
			posts[i] = sub('(:+-*\(+)|(\(\(+)', 'sad.', smile)
		except Exception:
			posts[i] = ''
	return posts

def stemData(posts):
	from nltk.stem.snowball import RussianStemmer
	from nltk import word_tokenize, sent_tokenize
	stemmer = RussianStemmer()
	for i in range(0, len(posts)):
		sentences = sent_tokenize(posts[i])
		for j in range(0, len(sentences)):
			words = word_tokenize(sentences[j])
			for k in range(0, len(words)):
				words[k] = stemmer.stem(words[k])
			sentences[j] = u' '.join(words)
		posts[i] = u''.join(sentences)
	return posts

def train():
	from pybrain.tools.shortcuts import buildNetwork
	net = buildNetwork(1, 1, 100)

filename = 'train_content.csv'

def do():
	# x = parseData(filename)
	x = [u'Привет! Как дела? А я вот по улице гуляю... Ага, так и есть :)']
	y = stemData(x)
	print y[0]

do()
