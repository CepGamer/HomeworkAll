__author__ = 'Sergei Bolotov'

from PIL import Image
import numpy
import random
import copy

inputf = 'peppers.jpg'
output = 'out{}.jpg'

image = numpy.array(Image.open(inputf))
dots = image.reshape((image.shape[0] * image.shape[1], image.shape[2]))

# res

def selectKRand(w, k):
    random.seed()
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
        min = 1000000000.0
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

def minimisation(w, clusters, k):
    mins = []
    for i in range(0, k):
        mins += [numpy.array((0.0, 0.0, 0.0))]
    count = [0] * k
    for i, x in enumerate(w):
        for ind in range(0, x.size):
            a = x[ind].astype(int)
            mins[clusters[i]][ind] += a
        count[clusters[i]] += 1
    for i in range(0, len(mins)):
        for y in range(0, mins[0].size):
            mins[i][y] /= count[i]
    return mins

def kmeans(w, k, max = 15):
    # STEP 1
    centres = selectKRand(w, k)
    # STEP 2
    clusters = classify(w, centres)
    # STEP 3
    mins = minimisation(w, clusters, k)
    nmins = mins
    cond = True
    max -= 1
    while cond:
        clusters = classify(w, nmins)
        nmins = minimisation(w, clusters, k)
        for i in range(0, len(nmins)):
            if (nmins[i] == mins[i]).all():
                cond = False
                break
        mins = nmins
        if max <= 0:
            cond = False
        max -= 1
    func = 0
    for _, x in enumerate(w):
        for ind in range(0, x.size):
            a = x[ind].astype(int)
            b = nmins[clusters[i]][ind]
            func += (a - b) * (a - b)
    return (func, clusters, mins)

kmeanses = 5
color = []

for k in range(2, 4):
    W = copy.deepcopy(dots)
    val, clusters, color = kmeans(W, k)
    bestClusters = clusters
    for i in range(1, kmeanses):
        l, clusters, cols = kmeans(W, k)
        if l < val:
            val = l
            bestClusters = clusters
            color = cols

    for i in range(W.size / W[0].size):
        W[i] = color[bestClusters[i]]

    res = W.reshape(image.shape)
    Image.fromarray(res).save(output.format(k))
