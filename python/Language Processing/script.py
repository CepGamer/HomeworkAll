# coding=UTF-8

happy = u'крибибопа'
sad = u'квазиблипа'

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
    fi = open(trainData, 'r')
    f = fi.read().decode('utf8').split('\n')
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
    fi.close()
    return posts

def stemData(posts):
    global happy
    global sad
    
    global shouldStemData
    
    from nltk.stem.snowball import RussianStemmer
    from nltk import word_tokenize, sent_tokenize
    stemmer = RussianStemmer()
    toRet = []
    if shouldStemData:
        # renew smiles
        happy = stemmer.stem(happy)
        sad = stemmer.stem(sad)
        
    for i in range(0, len(posts)):
        sentences = sent_tokenize(posts[i])
        for j in range(0, len(sentences)):
            words = word_tokenize(sentences[j])
            import string
            for k in range(0, len(words)):
                try:
                    if shouldStemData:
                        words[k] = unicode(stemmer.stem(words[k]))
                    # words[k] = cyr_to_r(words[k]).encode('utf8')
                    letters = u'абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'
                    words[k] = filter(lambda x: x in letters + string.letters + string.digits + '.!?', words[k])
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
    t = u'Positive smile ({}) alike:\n'.format(happy)
    for x in model.most_similar(positive = [happy], negative = [sad], topn = 25):
        t += x[0] + ' ' + str(x[1])
        t += '\n'
    t += '\n'
    for x in model.most_similar(positive = [happy], negative = [], topn = 25):
        t += x[0] + ' ' + str(x[1])
        t += '\n'
    t += u'\nNegative smile ({}) alike:\n'.format(sad)
    for x in model.most_similar(positive = [sad], negative = [happy], topn = 25):
        t += x[0] + ' ' + str(x[1])
        t += '\n'
    t += '\n'
    for x in model.most_similar(positive = [sad], negative = [], topn = 25):
        t += x[0] + ' ' + str(x[1])
        t += '\n'
    print t
    return t
    
trainData = 'train_content.csv'
testData = 'test_content.csv'

modelname = 'word2vec.csv'

shouldStemData = True
shouldSaveModel = True

def do():
    global shouldStemData
    global shouldSaveModel
    from os.path import isfile
    from gensim.models import Word2Vec
    from sys import argv
        
    if not isfile(modelname) or (len(argv) > 1 and argv[1] == '--update'):
        parsed = parseData(trainData)
        print 'Begin stemming data'
        parsed = stemData(parsed)
        if False:
            try:
                print 'Write stemmed data'
                f = open('stemmed_data.csv', 'w')
                f.write('\n'.join(map(lambda x: ' '.join(x), parsed)))
            except Exception:
                print 'Failed to write'
            finally:
                try:
                    f.close()
                except Exception:
                    print ''

        print 'Begin training'
        if len(argv) > 1 and argv[1] == '--update':
            print 'Update model'
            model = Word2Vec.load(modelname)
            model.train(sentences=parsed)
        else:
            model = train(parsed)
        
        if shouldSaveModel:
            print 'Save model'
            model.save(modelname)

    else:
        stemData([])
        model = Word2Vec.load(modelname)

    print 'Get results'
    # try:
    t = getResults(model)
    print model.similarity(happy, sad)
    open('res.txt', 'w').write(t.encode('utf8'))
    # except Exception, e:
    #     print 'ошибка: ' + e

do()
