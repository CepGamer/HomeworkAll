from cv2 import *
import numpy as np

img = imread("mandril.bmp", IMREAD_GRAYSCALE)

if __name__ == "__main__":
    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)
    magnitude_spectrum = 20*np.log(np.abs(fshift))

    imshow("Original Image", img)
    imshow("Magnitude Spectrum", magnitude_spectrum.astype(np.uint8))
    waitKey(0)

    rows, cols = img.shape
    crow,ccol = rows/2 , cols/2
    fshift[crow-30:crow+30, ccol-30:ccol+30] = 0
    f_ishift = np.fft.ifftshift(fshift)
    img_back = np.fft.ifft2(f_ishift)
    img_back = np.abs(img_back)

    imshow("Original Image", img)
    imshow('Image after HPF', img_back.astype(np.uint8))
    waitKey(0)

    lKernel = 1
    lapl = Laplacian(img, 0, img, lKernel, 3)

    imshow("Laplacian", lapl)
    waitKey(0)

    imwrite("fourier.png", img_back)
    imwrite("lapl.png", lapl)
