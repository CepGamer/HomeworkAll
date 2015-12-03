# coding=UTF-8

def parseData(filename):
	from nltk.stem.snowball import RussianStemmer
	from re import sub
	f = open(filename, 'r').read().split('\n')
	posts = [0] * len(f)
	for i, string in enumerate(f):
		try:
			smile = sub('(:-*\)+)|(\)\)+)', 'smile', string.split('\t')[3])
			posts[i] = sub('(:+-*\(+)|(\(\(+)', 'sad', smile)
		except Exception:
			posts[i] = ''
	
	
	stemmer = RussianStemmer()
	

def train():
	from pybrain.tools.shortcuts import buildNetwork
	net = buildNetwork(1, 1, 100)

filename = 'train_content.csv'

parseData(filename)
