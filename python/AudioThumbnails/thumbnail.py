import numpy as np
from librosa import load, get_duration
from librosa.feature import chroma_stft
from librosa.display import specshow
import sys
import math
from datetime import timedelta
from time import time

if len(sys.argv) < 2:
    print "Usage: %s <source_filename>" % sys.argv[0]
    sys.exit(1)

def printDt(s, f):
    print 'Total passed: ' + str(timedelta(seconds = f - s))

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
dur = get_duration(y=src, sr=samplerate)

# constants
chromas = 12

# set time
stime = time()

# get chromagram
print 'get chromagram'
chromagram = chroma_stft(y = src, sr = samplerate)

printDt(stime, time())

# count correlation
print chromagram.shape
print 'count correlation'
correlation = np.corrcoef(
    np.cov(np.transpose(chromagram)))

printDt(stime, time())

thumbnailSize = int(22 / dur * correlation.size)

# filter correlation
print 'filter correlation'
mx = 0
mix = 0
mjx = 0
for i in range(0, correlation.size):
    item = np.diagonal(correlation, offset = -i)
    if i % 10 == 0:
        print i
    for j in range(0, correlation.size - i):
        x = 0
        x = max(np.sum(item[j:j + thumbnailSize]), x)
        if x > mx:
            mx = x
            mix = i
            mjx = j

printDt(stime, time())

print 'start point:'
print mix / correlation.size * dur
print 'lag:'
print mjx / correlation.size * dur

# show graph
# specshow(correlation, y_axis = "chroma", x_axis = "time")
# plot.colorbar()
# plot.title("Chromagram")
# plot.tight_layout()
# plot.show()

