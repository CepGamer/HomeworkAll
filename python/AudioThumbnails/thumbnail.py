import numpy as np
from librosa import load, get_duration
from librosa.feature import chroma_stft
from librosa.display import specshow
import sys
import math
from datetime import timedelta
from time import time
from multiprocessing import Pool

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

print 'Start reading file'
# read file
src, samplerate = load(songname)
dur = get_duration(y=src, sr=samplerate)

# set time
stime = time()

# get chromagram
print 'get chromagram'
chromagram = chroma_stft(y = src, sr = samplerate, hop_length = 512 * 8)

printDt(stime, time())

# count correlation
print 'count correlation'
correlation = np.corrcoef(
    np.cov(np.transpose(chromagram)))

corsize = correlation.shape[0]

printDt(stime, time())

thumbnailSize = int(22 / dur * corsize)
startSec = int(5 / dur * corsize)

# filter correlation
print 'filter correlation'
# procs = Pool()
mx = 0
mix = 0
mjx = 0
for i in range(thumbnailSize, corsize):
    item = np.diagonal(correlation, offset = -i)
    for j in range(startSec, corsize - i):
        x = max(np.sum(item[j:j + thumbnailSize]), 0)
        if x > mx:
            mx = x
            mix = i
            mjx = j

printDt(stime, time())

print 'value:'
print mx
print 'start point:'
print mjx * dur / corsize
print 'lag:'
print mix * dur / corsize 

# show graph
# specshow(correlation, y_axis = "chroma", x_axis = "time")
# plot.colorbar()
# plot.title("Chromagram")
# plot.tight_layout()
# plot.show()

