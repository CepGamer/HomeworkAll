__author__ = 'Sergei Bolotov'

import task2 as km
import numpy as np
from math import sqrt

def bgss(w, centers, ns, degree = 2):
    g = km.barycenter(w)
    res = 0
    for i, c in enumerate(centers):
        x = pow(np.linalg.norm(g - c), degree)
        res += ns[i] * x
    return res

def wgss(w, clusters, center, clustNum, degree = 2):
    res = 0
    for i, x in enumerate(w):
        if clustNum == clusters[i]:
            t = pow(np.linalg.norm(x - center), degree)
            res += t
    return res

def readExt(inputf):
    f = open(inputf, 'r')
    s = f.read().split("\r\n")
    if s[-1] == '':
        s = s[:-1]
    res = np.empty([len(s), len(s[0].split(' ')) - 1])
    ideal = [0] * len(s)
    for i, vals in enumerate(s):
        x = vals.split(' ')
        res[i] = np.array((float(x[1]), float(x[2])))
        ideal[i] = int(x[0])
    
    return ideal, res

if __name__ == "__main__":
    inputf = "peppers.jpg"
    w = km.readImg(inputf)
    minK, maxK = 2, 20

    # init indices
    DavBoul  = [0] * (maxK - minK + 1)
    CalHar   = [0] * (maxK - minK + 1)
    Rand     = [0] * (maxK - minK + 1)
    FowMal   = [0] * (maxK - minK + 1)
    
    for k in range(minK, maxK + 1):
        try:
            x, clusters, y = km.kmeans(w, k)
            centers = km.minimisation(w, clusters, k)
            
            # prelim counts
            ns = [0] * k
            for i in clusters:
                ns[i] += 1
            tb = False
            for i in ns:
                if i == 0:
                    tb = True
                    break
            if tb:
                continue
    
            # CalHar count
            wgssSum = 0
            bgssSum = bgss(w, centers, ns)
            for i in range(k):
                wgssSum += wgss(w, clusters, centers[i], i)
            CalHar[k - minK] = bgssSum * (len(clusters) - k) / (wgssSum * (k - 1))
            
            # DavBoul count
            meanDists = [0] * k
            for i in range(k):
                meanDists[i] = wgss(w, clusters, centers[i], i, 1) / ns[i]
            for i in range(k):
                t = 0
                for j in range(k):
                    if i != j:
                        t = max(t, (meanDists[i] + meanDists[j]) / np.linalg.norm(centers[i] - centers[j]))
                DavBoul[k - minK] += t / k
            
            # External prelim
            ideal, externals = readExt("task_3_data_7.txt")
            x, clusters, y = km.kmeans(externals, k)

            yy = 0
            yn = 0
            ny = 0
            nn = 0
            for i in range(len(ideal)):
                for j in range(i + 1, len(ideal)):
                    if ideal[i] == ideal[j]:
                        if clusters[i] == clusters[j]:
                            yy += 1
                        else:
                            yn += 1
                    else:
                        if clusters[i] == clusters[j]:
                            ny += 1
                        else:
                            nn += 1
            
            # Rand count
            Rand[k - minK] = (yy + nn) / len(clusters)
            
            # FowMal count
            FowMal[k - minK] = yy / (sqrt((yy + yn) * (yy + ny)))
            
        except Exception:
            pass

    print "From " + str(minK) + " to " + str(maxK)
    print "DavBoul: " + str(DavBoul)
    print "CalHar: " + str(CalHar)
    print "Rand: " + str(Rand)
    print "FowMal: " + str(FowMal)
    
    for arr in [DavBoul, CalHar]:
        m = (0, 0)
        for i, x in enumerate(arr):
            if x > m[1]:
                m = i, x
        print "Best num: " + str(m[0] + minK)
        km.getImg(inputf, m[0] + minK)
