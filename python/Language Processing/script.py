# coding=UTF-8

def parseData(filename):
	from nltk.stem.snowball import RussianStemmer
	# f = open(filename, 'r')
	stemmer = RussianStemmer()

def train():
	from pybrain.tools.shortcuts import buildNetwork
	net = buildNetwork(1, 1, 100)

filename = 'train_content.csv'

parseData(filename)
