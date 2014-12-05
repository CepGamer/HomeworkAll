from cv2 import *
from math import cos, sin, pi, sqrt
import numpy as np

img = imread("mandril.bmp", IMREAD_GRAYSCALE)

def transformPoint(pt, M):
    rt = np.dot(M, (pt[0], pt[1], 1.0))
    return rt.tolist()

def dist(x, y):
    a = x[0] - y[0]
    b = x[1] - y[1]
    return sqrt(a * a + b * b)

def percentMatching(matrix, matches, kp, kpChanged):
    g = 0
    for mc in matches:
        if dist(transformPoint(kp[mc.queryIdx].pt, matrix), kpChanged[mc.trainIdx].pt) < 1:
            g += 1
    return (g * 100) / len(matches)

if __name__ == "__main__":
    sift = SIFT()
    kp, des = sift.detectAndCompute(img, None)
    imgOrigKP = drawKeypoints(img, kp)
#    imshow("Special points", imgOrigKP)
#    waitKey(0)

    rows, cols = img.shape
    M = getRotationMatrix2D((cols / 2, rows / 2), 45, 0.5)
    rotatedImg = warpAffine(img, M, img.shape)
    kpRot, desRot = sift.detectAndCompute(rotatedImg, None)
    imRotatedKP = drawKeypoints(rotatedImg, kpRot)
#    imshow("Special points, Rotated", imRotatedKP)
#    waitKey(0)

    FLANN_INDEX_KDTREE = 0
    index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
    search_params = dict(checks=50)   # or pass empty dictionary
    flann = FlannBasedMatcher(index_params,search_params)

    bf = BFMatcher(NORM_L2, crossCheck = True)

#    matches = bf.match(des, desRot)
    matches = flann.match(des, desRot)

    matches = sorted(matches, key = lambda x: x.distance)
    result = percentMatching(M, matches, kp, kpRot)
    print result
    file = open("out.txt", 'w')
    file.write(str(result))
    file.close()
