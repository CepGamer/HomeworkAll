__author__ = 'Sergei Bolotov'

import task2 as km
import numpy as np

def bgss(w, clusters, centers):
    g = km.barycenter(w)
    ns = [0] * len(centers)
    res = 0
    for i in clusters:
        ns[i] += 1
    for i, c in enumerate(centers):
        x = np.euclidean(g, c)
        x *= 2
        res += ns[i] * x
    return res

def wgss(w, clusters, center, clustNum):
    res = 0
    for i, x in enumerate(w):
        t = np.euclidean(x, center)
        t *= 2
        res += t
    return res

if __name__ = "main":
    inputf = "peppers.jpg"
    w = km.readImg(inputf)
    
    minK, maxK = 1, 2

    # init indices
    DavBoul  = [0] * (maxK - minK + 1)
    CalHar   = [0] * (maxK - minK + 1)
    Rand     = [0] * (maxK - minK + 1)
    FowMal   = [0] * (maxK - minK + 1)
    
    for k in range(minK, maxK + 1):
        x, clusters, y = km.kmeans(w, k)
        centers = km.minimisation(w, clusters, k)
        
        # DavBoul count
        
        # CalHar count
        wgssSum = 0
        bgssSum = bgss(w, clusters, centers)
        for i in range(k):
            wgssSum += wgss(w, clusters, centers[i], i)
        CalHar[k - minK] = bgssSum * (len(clusters) - k) / (wgssSum * (k - 1))
        
        # Rand count
        
        # FowMal count
        
    print "From " + str(minK) " to " + str(maxK)
    print "DavBoul: " + str(DavBoul)
    print "CalHar: " + str(CalHar)
    print "Rand: " + str(Rand)
    print "FowMal: " + str(FowMal)
