__author__ = 'Sergei Bolotov'

from PIL import Image
import numpy
import random

inputf = 'peppers.jpg'
output = 'out.jpg'

image = numpy.array(Image.open(inputf))
W = image.reshape((image.shape[0] * image.shape[1], image.shape[2]))

# res

def selectKRand(w, k):
    n = w.size / w[0].size
    if k > n:
        return []
    if k == n:
        return range(0, k)
    res = []
    resx = []
    for i in range(0, k):
        x = random.randint(0, n - 1)
        while x in res:
            x = random.randint(0, n - 1)
        res += [x]
        resx += [w[x]]
    return resx

def classify(w, centres):
    ret = []
    for i, x in enumerate(w):
        min = 1000000000
        mini = 0
        for id, c in enumerate(centres):
            l = 0
            for ind in range(0, x.size):
                a = x[ind].astype(int)
                b = c[ind].astype(int)
                l += (a - b) * (a - b)
            if min > l:
                mini = id
                min = l
        ret += [mini]
    return ret

def kmeans(w, k):
    centres = selectKRand(w, k)
    clusters = []
    # for i, x in enumerate(w):


# res = res.reshape(image.shape)
# Image.fromarray(res).save(output)
