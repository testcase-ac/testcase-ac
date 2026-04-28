idx = 1

import sys
r = sys.stdin.readline
x = int(r())

def idx_cal(idx):
    return (idx*idx+idx)//2
while(idx_cal(idx) < x):
    idx += 1

cur_idx = x - idx_cal(idx-1)
if idx % 2 == 1:
    print("{}/{}".format(idx+1-cur_idx, cur_idx))
else:
    print("{}/{}".format(cur_idx, idx+1-cur_idx))
