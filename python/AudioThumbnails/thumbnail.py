import numpy as np
from aubio import fft, source, fvec
from pydub import AudioSegment
import sys
import math

if len(sys.argv) < 2:
    print "Usage: %s <source_filename>" % sys.argv[0]
    sys.exit(1)

win_s = 512                 # fft size
hop_s = win_s / 4           # hop size

songname = sys.argv[1].split('.')
if songname[-1] == 'mp3':
	song = AudioSegment.from_mp3('.'.join(songname))
	songname[-1] = "wav"
	songname = '.'.join(songname)
	song.export(songname, format = "wav")
else:
	songname = '.'.join(songname)

# read file
src = source(songname, 0, hop_s)
f = fft(win_s)
chromas = 12
# chromagram = np.ndarray(shape = (0, chromas), dtype = float)
chromagram = []
# constants
maxSum = 1500

window = 0
# get chromagram
while True:
    samples, read = src()
    fftgrain = f(samples)
    if np.sum(fftgrain.norm) > maxSum:
		continue
    # tmp = np.ndarray(buffer=np.zeros(chromas), shape = (chromas, 1), dtype = float)
    tmp = [0] * 12
    for i, x in enumerate(fftgrain.phas):
        if x <= 0 or math.isnan(x) or math.isnan(fftgrain.norm[i]):
            continue
        lg = math.log(x, 2)
        c = lg - math.floor(lg) + 1 / 24
        c *= chromas
        c = int(c) % chromas
        tmp[c] += fftgrain.norm[i]

    chromagram += [tmp]
    window += 1
    if read < hop_s or window == 100:
        break

print 'Start resize'
chromagram = np.ndarray(buffer=np.array(chromagram), shape = (chromas, len(chromagram)), dtype = float)

# count correlation

