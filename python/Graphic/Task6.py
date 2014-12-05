from cv2 import *
import numpy as np

def detect(frame, fast = False):
    if not fast:
        feature_params = dict( 
                        maxCorners = 100,
                        qualityLevel = 0.1,
                        minDistance = 5,
                        blockSize = 7,
                        useHarrisDetector = True )
        return goodFeaturesToTrack(frame, mask = None, **feature_params)
    else:
        Fast = FastFeatureDetector(125, FAST_FEATURE_DETECTOR_TYPE_9_16)
        kp = Fast.detect(frame, None)
        toRet = [np.float32( np.array([np.array(x.pt)])) for x in kp]
        return np.array(toRet)

def drawFlow(video, fast = False):
    lk_params = dict( winSize  = (10, 10),
                      maxLevel = 2,
                      criteria = (TERM_CRITERIA_EPS | TERM_CRITERIA_COUNT, 10, 0.03))

    color = np.random.randint(0, 255, (100,3))

    ret, old = video.read()
    oldG = cvtColor(old, COLOR_BGR2GRAY)

    fourcc = cv.CV_FOURCC(*'DIVX')
    outName = 'outputFast.avi' if fast else 'outputHarris.avi'
    out = VideoWriter(outName, fourcc, 20.0, oldG.shape)

    pointsO = detect(oldG, fast)
    
    mask = np.zeros_like(old)

    while(True):
        ret, curr = video.read()
        if not ret:
            break
        currG = cvtColor(curr, COLOR_BGR2GRAY)

        pointsC, st, err = calcOpticalFlowPyrLK(oldG, currG, pointsO, None, **lk_params)

        goodC = pointsC[st == 1]
        goodO = pointsO[st == 1]

        for i, (new, old) in enumerate(zip(goodC, goodO)):
            a, b = new.ravel()
            c, d = old.ravel()
            line(mask, (a, b), (c, d), color[i % 100].tolist(), 2)
            circle(curr, (a, b), 5, color[i % 100].tolist(), -1)
        img = add(curr, mask)
        out.write(img)

        imshow('frame', img)
        k = waitKey(30) & 0xff
        if k == 27:
            break
        oldG = currG.copy()
        pointsO = goodC.reshape(-1, 1, 2)
    return out

if __name__ == "__main__":
    video = VideoCapture('sequence.mpg')
    vid = drawFlow(video, True)
    vid.release()

    video = VideoCapture('sequence.mpg')
    vid = drawFlow(video, False)
    vid.release()

    waitKey(0)
