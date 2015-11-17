import numpy as np
from librosa import load
from librosa.feature import chroma_stft
from librosa.display import specshow
import sys
import math
import matplotlib.pyplot as plot

if len(sys.argv) < 2:
    print "Usage: %s <source_filename>" % sys.argv[0]
    sys.exit(1)

win_s = 512                 # fft size
hop_s = win_s / 4           # hop size

songname = sys.argv[1].split('.')
if songname[-1] == 'mp3':
    from pydub import AudioSegment
    song = AudioSegment.from_mp3('.'.join(songname))
    songname[-1] = "wav"
    songname = '.'.join(songname)
    song.export(songname, format = "wav")
else:
    songname = '.'.join(songname)

# read file
src, samplerate = load(songname)

print samplerate
# constants
chromas = 12

# get chromagram
chromagram = np.transpose(chroma_stft(y = src, sr = samplerate))
for i, _ in enumerate(chromagram):
    chromagram[i] = np.divide(chromagram[i], math.sqrt(np.dot(chromagram[i], chromagram[i])))

# count correlation
correlation = np.dot(chromagram, np.transpose(chromagram))

# filter correlation
t = np.ndarray(buffer = np.zeros(correlation.shape[0] * correlation.shape[1]), shape=correlation.shape, dtype = float)
for i in range(0, correlation.size):
    for j in range(0, correlation.size):
        for k in range(5, 60):
            if k + i + j >= correlation.size:
                break
            t[i][j] += correlation[i + k][i + j + k]

res = np.argmax(t)
print res / t.size
print res % t.size

# show graph
# specshow(correlation, y_axis = "chroma", x_axis = "time")
# plot.colorbar()
# plot.title("Chromagram")
# plot.tight_layout()
# plot.show()

