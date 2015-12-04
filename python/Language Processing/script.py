# coding=UTF-8

happy = u'happy'
sad = u'sad'

def parseData(filename):
	from re import sub
	f = open(filename, 'r').read().split('\n')
	posts = [0] * len(f)
	for i, string in enumerate(f):
		try:
			smile = sub(u'(:-*\)+)|(\)\)+)', happy + u'.', string.split('\t')[3])
			posts[i] = sub(u'(:+-*\(+)|(\(\(+)', sad + u'.', smile)
		except Exception:
			posts[i] = ''
	return posts

def stemData(posts):
	from nltk.stem.snowball import RussianStemmer
	from nltk import word_tokenize, sent_tokenize
	stemmer = RussianStemmer()
	# renew smiles
	happy = stemmer.stem(happy)
	sad = stemmer.stem(sad)
	
	toRet = []
	for i in range(0, len(posts)):
		sentences = sent_tokenize(posts[i].decode('utf8'))
		for j in range(0, len(sentences)):
			words = word_tokenize(sentences[j])
			for k in range(0, len(words)):
				try:
					words[k] = stemmer.stem(words[k])
				except Exception:
					print words[k]
			try:
				sentences[j] = u' '.join(words)
			except Exception:
				print words
				sentences[j] = ''
		toRet += sentences
	return toRet

def train(sentences):
	from gensim.models import Word2Vec
	model = Word2Vec(sentences, size=100)
	return model
	
def getResults(model):
	t = u'Positive smile alike:\n'
	for x in model.most_similar(positive = [happy], negative = [sad]):
		t += x
		t += u'\n'
	t += 'Negative smile alike:\n'
	for x in model.most_similar(positive = [sad], negative = [happy]):
		t += x
		t += u'\n'
	print t
	return t
	
filename = 'train_content.csv'

def do():
	x = parseData(filename)
	y = stemData(x)
	z = train(y)
	t = getResults(z)
	open('tmp.txt', 'w').write(t)
	
do()
