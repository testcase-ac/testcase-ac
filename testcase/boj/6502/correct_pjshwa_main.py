import sys, math

def fit(b):
    if b: return "fits"
    else: return "does not fit"

idx = 1
while(True):
    s = sys.stdin.readline().rstrip()
    if(len(s) == 1): break
    r, w, l = map(int, s.split())
    print("Pizza {} {} on the table.".format(idx, fit(2*r>=math.sqrt(w**2+l**2))))
    idx += 1