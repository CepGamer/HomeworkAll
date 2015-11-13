import time
import math
import datetime
import sqlite3
import random
import copy

dbFile = 'songlog.db'
db = sqlite3.connect(dbFile)

maxUsers = 0

userIds = map(lambda x: x[0] - 1, db.execute("select id from users" + ("limit {}".format(maxUsers) if maxUsers > 0 else "") + ";").fetchall())

userClusters = [0] * len(userIds)
userSongs = []
for i in range(0, len(userIds)):
    userSongs += [dict()]

# define clusters
clusterNum = 5
clusterCentres = [0] * clusterNum

globalRate = 0

# fetch songs for users
for id in userIds:
    global userSongs

    learn = zip(*db.execute('select song_id, amount from learnlog where user_id = {};'.format(id)).fetchall())
    if len(learn) == 0:
        continue
    songs = learn[0]
    m = max(learn[1])
    ratings = map(lambda x: x / m, learn[1])

    for i, song in enumerate(songs):
        userSongs[id][song] = ratings[i]
    if len(songs) > 0:
        userSongs[id][-1] = math.sqrt(sum(map(lambda x: x * x, learn[1])))
    globalRate = max([m, globalRate])

# Select random users as centroids
def getRand():
    random.seed()
    clusters = []
    n = len(userIds)
    for i in range(0, clusterNum):
        x = random.randint(0, n - 1)
        while x in clusters and len(userSongs[x]) > 0:
            x = random.randint(0, n - 1)
        clusters += [x]
        userClusters[x] = i
        clusterCentres[i] = copy.deepcopy(userSongs[x])

# Classify fun
def classify():
    global userClusters
    global userSongs
    global clusterCentres

    for id, dicti in enumerate(userSongs):
        maxs = 0
        maxi = 0
        for cid, cdict in enumerate(clusterCentres):
            x = 0
            for song in dicti:
                if song in cdict:
                    x += dicti[song] * cdict[song]
            if len(dicti) > 0 and cdict[-1] > 0:
                x /= dicti[-1] * cdict[-1]
            if x > maxs:
                maxs = x
                maxi = cid
        userClusters[id] = maxi

newCentres = [0] * clusterNum

# Minimise fun
def minimisation():
    global newCentres
    global userClusters
    global userSongs
    global clusterNum

    for i in range(0, clusterNum):
        newCentres[i] = dict()
    count = []
    for i in range(0, clusterNum):
        count += [dict()]
    for id, dicti in enumerate(userSongs):
        for song in dicti:
            if song in newCentres[userClusters[id]]:
                count[userClusters[id]][song] += 1
                newCentres[userClusters[id]][song] += dicti[song]
            else:
                count[userClusters[id]][song] = 1
                newCentres[userClusters[id]][song] = dicti[song]
    for i in range(0, clusterNum):
        x = 0
        for song in newCentres[i]:
            newCentres[i][song] /= count[i][song]
            x += (lambda x: x * x)(newCentres[i][song])
        newCentres[i][-1] = math.sqrt(x)

maxCount = 15

# Define clusters
def kMeans():
    global clusterCentres
    global newCentres
    global maxCount

    x = maxCount
    getRand()
    classify()
    minimisation()

    while x > 0:
        x -= 1
        classify()
        minimisation()
        if newCentres == clusterCentres:
            x = 0
        clusterCentres = copy.deepcopy(newCentres)

    retval = 0
    for id, user in enumerate(userSongs):
        x = 0
        for song in user:
            if song in clusterCentres[userClusters[id]]:
                x += user[song] * clusterCentres[userClusters[id]][song]
        if len(user) > 0 and clusterCentres[userClusters[id]][-1] > 0:
            x /= user[-1] * clusterCentres[userClusters[id]][-1]
        retval += x
    return retval

bestRes = []
bestVal = 0
kMeanses = 10

# run algo
for i in range(0, kMeanses):
    x = kMeans()
    if x > bestVal:
        bestRes = copy.deepcopy(clusterCentres)
        bestVal = x

clusterCentres = bestRes

test = zip(*db.execute('select user_id, song_id, amount from testlog;'))

def predict(id, song):
    cluster = userClusters[id]
    if song not in clusterCentres[cluster]:
        return 0
    return clusterCentres[cluster][song]

maeSum = 0
mseSum = 0
testCount = 0

for i, id in enumerate(test[0]):
    id -= 1
    if not userSongs[id]:
        continue
    pred = predict(id, test[1][i])
    d = math.fabs(float(test[2][i]) - pred)
    maeSum += d
    mseSum += d * d
    testCount += 1

nmae = (maeSum / testCount) / globalRate
nrmse = math.sqrt(mseSum / testCount) / globalRate

print "NMAE =", nmae
print "NRMSE =", nrmse

db.close()

