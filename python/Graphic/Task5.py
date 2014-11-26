from cv2 import *
import numpy as np

img = imread("mandril.bmp", IMREAD_GRAYSCALE)

if __name__ == "__main__":
    sift = SIFT()
    kp, des = sift.detectAndCompute(img, None)
    imgOrigKP = drawKeypoints(img, kp)
    imshow("Special points", imgOrigKP)
    waitKey(0)

    rows, cols = img.shape
    M = getRotationMatrix2D((cols / 2, rows / 2), 45, 0.5)
    rotatedImg = warpAffine(img, M, img.shape)
    kpRot, desRot = sift.detectAndCompute(rotatedImg, None)
    imRotatedKP = drawKeypoints(rotatedImg, kpRot)
    imshow("Special points, Rotated", imRotatedKP)
    waitKey(0)

    bf = BFMatcher(NORM_L2, crossCheck = True)
    matches = bf.match(des, desRot)
    pass

