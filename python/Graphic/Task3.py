from cv2 import *
import numpy
from Task2 import detectTextImg

img = imread("text.bmp")

origImg = img.copy()

img = detectTextImg(img, 1, 1)

def detectErode(img):
    for i in range(0, 5):
        x = getStructuringElement(MORPH_RECT,
                                  (2 * i + 1, 2 * i + 1),
                                  (i, i))
        img = erode(img, x)
        imshow("Display", img)
        waitKey(0)

def detectDilate(img):
    for i in range(0, 5):
        x = getStructuringElement(MORPH_RECT,
                                  (2 * i + 1, 2 * i + 1),
                                  (i, i))
        img = dilate(img, x)
        imshow("Display", img)
        waitKey(0)

def dilateImg(img, dilateCoef = 1):
    x = getStructuringElement(MORPH_RECT,
                              (2 * dilateCoef + 1, 2 * dilateCoef + 1),
                              (dilateCoef, dilateCoef))
    img = dilate(img, x)
    return img

def erodeImg(img, erodeCoef = 1):
    x = getStructuringElement(MORPH_RECT,
                              (2 * erodeCoef + 1, 2 * erodeCoef + 1),
                              (erodeCoef, erodeCoef))
    img = erode(img, x)
    return img

def findVal(img, x, y, h, w, val):
    for i in range(x, x + w):
        for j in range(y, y + h):
            if img[j][i] == val:
                return (i, j)

if __name__ == "__main__":
    dilateCoef = 1
    erodeCoef = 1
    
    img = dilateImg(img, dilateCoef)
    img = erodeImg(img, erodeCoef)
    img = dilateImg(img, dilateCoef)

    img = cvtColor(img, COLOR_BGR2GRAY)
    contours, hierarchy = findContours(img.copy(), RETR_EXTERNAL, CHAIN_APPROX_NONE)
    newVal = 255
    h, w = img.shape
    mask = numpy.zeros((h + 2, w + 2), numpy.uint8)

    for contour in contours:
        x, y, w, h = boundingRect(contour)
        rectangle(origImg, (x, y), (x + w, y + h), 255)
#        floodFill(img, mask, findVal(img, x, y, h, w, 255), 255)
#        imshow("Display", img)
#        waitKey(0)


    imshow("Display", origImg)
    imshow("Display1", img)
    imwrite("out.bmp", origImg)
    waitKey(0)
