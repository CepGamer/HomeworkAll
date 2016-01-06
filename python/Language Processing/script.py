# coding=UTF-8

import numpy as np

happy = u'крибибопа'
sad = u'квазиблипа'
invert = [u"не", u"нет"]

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
            smile = sub('(:-*\)+)|(\)\)+)', ' ' + happy + '. ', wo_pics)
            posts[i] = sub('(:+-*\(+)|(\(\(+)', ' ' + sad + '. ', smile)
        except Exception:
            if len(string) > 3:
                print 'Could not replace: ' + string.split('\t')[3]
            posts[i] = ''
    fi.close()
    return posts

def stemData(posts):
    global happy
    global sad
    global invert
    
    global shouldStemData
    
    from nltk.stem.snowball import RussianStemmer
    from nltk import word_tokenize, sent_tokenize
    from gensim.models.doc2vec import LabeledSentence
    stemmer = RussianStemmer()
    toRet = []
    curI = 0
    if shouldStemData:
        # renew smiles
        happy = stemmer.stem(happy)
        sad = stemmer.stem(sad)
    positives = []
    negatives = []
    
    for i in range(0, len(posts)):
        if i % 10000 == 0:
            print i
        sentences = sent_tokenize(posts[i])
        for j in range(0, len(sentences)):
            words = word_tokenize(sentences[j])
            import string
            for k in range(0, len(words)):
                try:
                    if shouldStemData and words[k] not in invert:
                        words[k] = unicode(stemmer.stem(words[k]))
                    # words[k] = cyr_to_r(words[k]).encode('utf8')
                    letters = u'абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'
                    words[k] = filter(lambda x: x in letters + string.letters + string.digits + '.!?', words[k])
                except Exception:
                    print 'failed word: ' + words[k]
                    raise Exception('')
            try:
                if words == []:
                    del sentences[j]
                    continue
                if words == [happy, '.']:
                    sentences[j] = LabeledSentence(words=words, tags=[happy])
                    if j > 0:
                        positives += [curI - 1]
                elif words == [sad, '.']:
                    sentences[j] = LabeledSentence(words=words, tags=[sad])
                    if j > 0:
                        negatives += [curI - 1]
                else:
                    if happy in words:
                        positives += [curI]
                        while happy in words:
                            words.remove(happy)
                    if sad in words:
                        negatives += [curI]
                        while sad in words:
                            words.remove(sad)
                    sentences[j] = LabeledSentence(words=words, tags=[str(curI)])
                curI += 1
            except Exception, e:
                print words
                sentences[j] = ['']
                raise e
        toRet += sentences
    return toRet, positives, negatives
    
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

def selectSmiles(posts, resFile):
    from nltk import sent_tokenize
    f = open(resFile, 'w')
    r = ''
    for x in posts:
        sents = sent_tokenize(x)
        for y in sents:
            if happy in y:
                r += y + '\n'
    try:
        f.write(r)
    except Exception:
        print ''
    finally:
        f.close()
    
trainData = "/tmp/train_content.csv"
testData = "/tmp/test_content.csv"

modelname = '/tmp/Doc2Vec.csv'

shouldStemData = True
shouldSaveModel = False

def do():
    global shouldStemData
    global shouldSaveModel
    from os.path import isfile
    from gensim.models import Doc2Vec
    from sys import argv

    if not isfile(modelname):# or (len(argv) > 1 and argv[1] == '--update'):
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
        if False:#len(argv) > 1 and argv[1] == '--update':
            print 'Update model'
            model = Doc2Vec.load(modelname)
            model.train(documents=parsed)
        else:
            model = Doc2Vec(documents=parsed)#, size=100, workers=4, window=5, min_count=5)
        
        if shouldSaveModel:
            print 'Save model'
            model.save(modelname)

    else:
        stemData([])
        model = Doc2Vec.load(modelname)

    print 'Get results'
    t = ''
    try:
        t = getResults(model)
    except Exception:
        for x in model.most_similar(happy):
            print x[0].encode('utf8')
    open('res.txt', 'w').write(t.encode('utf8'))
    # except Exception, e:
    #     print 'ошибка: ' + e

def extract():
    parsed = parseData(trainData)
    selectSmiles(parsed, "res.csv")

def sumWords(sent, model):
    xi = [0] * len(sent.words)
    if len(sent.words) == 0:
        return np.array([])
    inverted = False
    for j, word in enumerate(sent.words):
        try:
            #if word in invert:
            #    inverted = True
            if inverted:
                xi[j] = model[model.most_similar(negative=[invert], topn=1)[0][0]]
                inverted = False
            else:
                xi[j] = model[word]
        except Exception:
            xi[j] = model.seeded_vector(word)
    while True:
        try:
            xi.remove(0)
        except Exception:
            break
    return np.divide(np.sum(xi, axis=0), len(xi))

def testRandForest(classifier, model, stemmed, poss):
    margin = 0.5
    guessedPos = 0
    guessedNeut = 0
    l = 0
    k = 0
    m = len(poss)
    randWords = [0] * 10
    for i in range(len(stemmed)):
        while m != 0 and l < m and poss[l] < i:
            l += 1
        if l == m:
            l -= 1
        x = sumWords(stemmed[i], model)
        y = [0]
        try:
            y = classifier.predict(x.reshape(1, -1))
        except Exception:
            pass
        if y[0] >= margin:
            if m != 0 and poss[l] == i:
                if k * (len(stemmed) / 10) < i:
                    try:
                        randWords[k] = stemmed[i].words
                        k += 1
                    except Exception:
                        print ''
                guessedPos += 1
        else:
            if m == 0 or poss[l] != i:
                guessedNeut += 1
    
    return guessedPos, guessedNeut, randWords

def closeToWord(stemmed, word, poss, model):
    xk = [0] * len(stemmed)
    yk = [0] * len(stemmed)
    l = 0
    m = len(poss)
    mm = len(stemmed)
    for i in range(len(stemmed)):
        if i % 100000 == 0:
            print i
        xk[i] = sumWords(stemmed[i], model)
        while m !=0 and l < m and poss[l] < i:
            l += 1
        if l == m:
            l -= 1
        yk[i] = 1 if m != 0 and poss[l] == i else 0
    return xk, yk

def classify():
    global shouldStemData
    global shouldSaveModel
    from os.path import isfile
    from gensim.models import Doc2Vec
    from sys import argv

    if not isfile(modelname):# or (len(argv) > 1 and argv[1] == '--update'):
        parsed = parseData(trainData)
        print 'Begin stemming data'
        #l = 351063
        #print parsed[l:l + 2]
        stemmed, poss, negs = stemData(parsed)
        #print stemmed
        print 'Begin training'
        model = Doc2Vec(documents=stemmed)#, size=100, workers=4, window=5, min_count=5)

        if shouldSaveModel:
            print 'Save model'
            model.save(modelname)

    else:
        stemData([])
        model = Doc2Vec.load(modelname)
    try:
        import gc
        gc.collect()
    except Exception:
        gc.collect()
    print "Train Classifier"
    from sklearn.ensemble import RandomForestClassifier
    Pos = RandomForestClassifier()
    x, y = closeToWord(stemmed, happy, poss, model)
    Pos.fit(x, y)
    print "Done with happy" 
    try:
        import gc
        gc.collect()
    except Exception:
        gc.collect()
    Neg = RandomForestClassifier()
#    x, y = closeToWord(stemmed, sad, negs, model)
#    Neg.fit(x, y)
    try:
        import gc
        gc.collect()
    except Exception:
        gc.collect()
    print 'Test'
    tparsed = parseData(testData)
    tstemmed, tposs, tnegs = stemData(tparsed)
    print "Begin testing"
    xp, yp, rp = testRandForest(Pos, model, tstemmed, tposs)
#    xn, yn, rn = testRandForest(Neg, model, tstemmed, tnegs)
    print "guessedPos: ", xp, " guessedNeut: ", yp
    print "Total pos: ", len(tposs), "Total: ", len(tstemmed)
    
#    print "guessedNeg: ", xn, " guessedNeut: ", yn
#    print "Total neg: ", len(tnegs), "Total: ", len(tstemmed)

    #print "Rand pos: ", rp
    #print "Rand neg: ", rn

classify()
