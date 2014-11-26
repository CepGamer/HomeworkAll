from cv2 import *

img = imread("text.bmp")

def detectTextImg(img, gKernel = 3, lKernel = 1):
    GaussianBlur(img, (gKernel, gKernel), 0, img)
    Laplacian(img, 0, img, lKernel, 3)
#    GaussianBlur(img, (11, 5), 0, img)
    threshold(img, 50, 255, THRESH_BINARY, img)
    return img

def detectGKern(img):
    for i in range(1, 10):
        img = detectTextImg(img, 2 * i + 1)
        imshow("Display", img)
        waitKey(0)

def detectLapl(img):
    for i in range(1, 10):
        img = detectTextImg(img, gKernel, 2 * i + 1)
        imshow("Display", img)
        waitKey(0)

if __name__ == "__main__":
    gKernel = 3
    lKernel = 1

    detectTextImg(img, gKernel, lKernel)

    imshow("out", img)

    imwrite("out.png", img)
    waitKey(0)
