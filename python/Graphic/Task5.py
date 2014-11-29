from cv2 import *
from math import cos, sin, pi, sqrt
import numpy as np

img = imread("mandril.bmp", IMREAD_GRAYSCALE)

def transformPoint(pt, center, coef = 2, alpha = pi / 4):
    x = (pt[0] + center[0]) / coef - center[0]
    y = (pt[1] + center[1]) / coef - center[1]
    nx = +x * cos(alpha) + y * sin(alpha)
    ny = -x * sin(alpha) + y * cos(alpha)
    return (nx + center[0], ny + center[1])

def dist(x, y):
    a = x[0] - y[0]
    b = x[1] - y[1]
    return sqrt(a * a + b * b)

def percentMatching(midPoint, matches, kp, kpChanged):
    g = 0
    for mc in matches:
        if dist(transformPoint(kp[mc.queryIdx].pt, midPoint), kpChanged[mc.trainIdx].pt) < 5:
            g += 1
    return (g * 100) / len(matches)

if __name__ == "__main__":
    sift = SIFT()
    kp, des = sift.detectAndCompute(img, None)
    imgOrigKP = drawKeypoints(img, kp)
    imshow("Special points", imgOrigKP)
#    waitKey(0)

    rows, cols = img.shape
    M = getRotationMatrix2D((cols / 2, rows / 2), 45, 0.5)
    rotatedImg = warpAffine(img, M, img.shape)
    kpRot, desRot = sift.detectAndCompute(rotatedImg, None)
    imRotatedKP = drawKeypoints(rotatedImg, kpRot)
    imshow("Special points, Rotated", imRotatedKP)
#    waitKey(0)

    bf = BFMatcher(NORM_L2, crossCheck = True)
    matches = bf.match(des, desRot)

    matches = sorted(matches, key = lambda x: x.distance)
    result = percentMatching((cols / 2, rows / 2), matches, kp, kpRot)
    file = open("out.txt", 'w')
    file.write(str(result))
    file.close()
