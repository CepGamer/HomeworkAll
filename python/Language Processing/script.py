# coding=UTF-8

happy = u'happy'
sad = u'sad'

def cyr_to_r(word):
	word = (word.replace(u"а", "a").replace(u"а", "a")
				.replace(u"б", "b").replace(u"б", "b")
				.replace(u"в", "v").replace(u"в", "v")
				.replace(u"г", "g").replace(u"г", "g")
				.replace(u"д", "d").replace(u"д", "d")
				.replace(u"е", "e").replace(u"е", "e")
				.replace(u"ё", "e").replace(u"ё", "e")
				.replace(u"ж", "zh").replace(u"ж", "zh")
				.replace(u"з", "z").replace(u"з", "z")
				.replace(u"и", "i").replace(u"и", "i")
				.replace(u"й", "i`").replace(u"й", "i`")
				.replace(u"к", "k").replace(u"к", "k")
				.replace(u"л", "l").replace(u"л", "l")
				.replace(u"м", "m").replace(u"м", "m")
				.replace(u"н", "n").replace(u"н", "n")
				.replace(u"о", "o").replace(u"о", "o")
				.replace(u"п", "p").replace(u"п", "p")
				.replace(u"р", "r").replace(u"р", "r")
				.replace(u"с", "s").replace(u"с", "s")
				.replace(u"т", "t").replace(u"т", "t")
				.replace(u"у", "u").replace(u"у", "u")
				.replace(u"ф", "f").replace(u"ф", "f")
				.replace(u"х", "kh").replace(u"х", "kh")
				.replace(u"ц", "t^s").replace(u"ц", "t^s")
				.replace(u"ч", "ch").replace(u"ч", "ch")
				.replace(u"ш", "sh").replace(u"ш", "sh")
				.replace(u"щ", "shch").replace(u"щ", "shch")
				.replace(u"ъ", "''").replace(u"ъ", "''")
				.replace(u"ы", "y").replace(u"ы", "y")
				.replace(u"ь", "'").replace(u"ь", "'")
				.replace(u"э", "e`").replace(u"э", "e`")
				.replace(u"ю", "i^u").replace(u"ю", "i^u")
				.replace(u"я", "i^a").replace(u"я", "i^a"))

	return word

def parseData(trainData):
	global happy
	global sad
	from re import sub
	f = open(trainData, 'r').read().decode('utf8').split('\n')
	posts = [0] * len(f)
	for i, string in enumerate(f):
		try:
			wo_pics = sub('Images\[[0123456789]+(, [0123456789]+)*\]', 'Images', string.split('\t')[3])
			smile = sub('(:-*\)+)|(\)\)+)', happy, wo_pics)
			posts[i] = sub('(:+-*\(+)|(\(\(+)', sad, smile)
		except Exception:
			if len(string) > 3:
				print 'Could not replace: ' + string.split('\t')[3]
			posts[i] = ''
	return posts

def stemData(posts):
	global happy
	global sad
	from nltk.stem.snowball import RussianStemmer
	from nltk import word_tokenize, sent_tokenize
	stemmer = RussianStemmer()
	# renew smiles
	happy = stemmer.stem(happy)
	sad = stemmer.stem(sad)
	
	toRet = []
	for i in range(0, len(posts)):
		sentences = sent_tokenize(posts[i])
		for j in range(0, len(sentences)):
			words = word_tokenize(sentences[j])
			for k in range(0, len(words)):
				try:
					words[k] = cyr_to_r(unicode(stemmer.stem(words[k]))).encode('utf8')
				except Exception:
					print 'failed word: ' + words[k]
					raise Exception('')
			try:
				sentences[j] = words
			except Exception:
				print words
				sentences[j] = ['']
		toRet += sentences
	return toRet

def train(sentence):
	from gensim.models import Word2Vec
	model = Word2Vec(sentences=sentence, size=100, workers=4, window=5, min_count=5)
	return model
	
def getResults(model):
	global happy
	global sad
	t = 'Positive smile alike:\n'
	for x in model.most_similar(positive = [happy], negative = [sad]):
		t += x[0] + ' ' + str(x[1])
		t += '\n'
	t += 'Negative smile alike:\n'
	for x in model.most_similar(positive = [sad], negative = [happy]):
		t += x[0] + ' ' + str(x[1])
		t += '\n'
	print t
	return t
	
trainData = 'train_content.csv'
modelname = 'word2vec.csv'

def do():
	from os.path import isfile
	from gensim.models import Word2Vec
	if not isfile(modelname):
		parsed = parseData(trainData)
		print 'Begin stemming data'
		stemmed = stemData(parsed[0:100000])
		try:
			print 'Write stemmed data'
			f = open('stemmed_data.csv', 'w')
			f.write('\n'.join(stemmed))
		except Exception:
			print 'Failed to write'
		finally:
			f.close()
		
		print 'Begin training'
		model = train(stemmed)
		
		print 'Save model'
		model.save(modelname)
	else:
		stemData([])
	
	model = Word2Vec.load(modelname)
	
	print 'Get results'
	t = getResults(model)
	open('tmp.txt', 'w').write(t)
	
do()
