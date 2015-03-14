from cv2 import *
import numpy
# from Task2 import detectTextImg

img = imread("text.bmp")

origImg = img.copy()

def detectTextImg(img, gKernel = 3, lKernel = 1):
    GaussianBlur(img, (gKernel, gKernel), 0, img)
    Laplacian(img, 0, img, lKernel, 3)
#    GaussianBlur(img, (11, 5), 0, img)
    threshold(img, 50, 255, THRESH_BINARY, img)
    return img

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
    # contours, hierarchy = findContours(img.copy(), RETR_EXTERNAL, CHAIN_APPROX_NONE)
    newVal = 255
    gh, gw = img.shape
    mask = numpy.zeros((gh + 2, gw + 2), numpy.uint8)

    for i in range(gh):
        for j in range(gw):
            if img[i, j] == 255:
                _, (x, y, w, h) = floodFill(img, mask, (j, i), 0)
                rectangle(origImg, (x, y), (x + w, y + h), 255)
#        
#        imshow("Display", img)
#        waitKey(0)


    imshow("Display", origImg)
    imshow("Display1", img)
    imwrite("out.bmp", origImg)
    waitKey(0)
