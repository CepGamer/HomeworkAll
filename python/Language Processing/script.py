# coding=UTF-8

happy = u'крибибопа'
sad = u'квазиблипа'

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
            smile = sub('(:-*\)+)|(\)\)+)', ' ' + happy + '. ' + happy + '.', wo_pics)
            posts[i] = sub('(:+-*\(+)|(\(\(+)', ' ' + sad + '. ' + sad + '.', smile)
        except Exception:
            if len(string) > 3:
                print 'Could not replace: ' + string.split('\t')[3]
            posts[i] = ''
    fi.close()
    return posts

label = u"ПРЕДЛ_{}"

def stemData(posts):
    global happy
    global sad
    
    global label
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
                if words == [happy, '.']:
                    sentences[j] = LabeledSentence(words=words, tags=[happy])
                elif words == [sad, '.']:
                    sentences[j] = LabeledSentence(words=words, tags=[sad])
                else:
                    sentences[j] = LabeledSentence(words=words, tags=[label.format(curI)])
                    curI += 1
            except Exception, e:
                print words
                sentences[j] = ['']
                raise e
        toRet += sentences
    return toRet
    
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

modelname = 'Doc2Vec.csv'

shouldStemData = True
shouldSaveModel = True

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
    try:
        t = getResults(model)
    except Exception:
        for x in model.most_similar(happy):
            print x[0].encode('utf8')
    open('res.txt', 'w').write(t.encode('utf8'))
    # except Exception, e:
    #     print 'ошибка: ' + e

do()
