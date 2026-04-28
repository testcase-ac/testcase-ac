r_dict = {
'black':0,
'brown':1,
'red':2,
'orange':3,
'yellow':4,
'green':5,
'blue':6,
'violet':7,
'grey':8,
'white':9
}

import sys
r = sys.stdin.readline
f = r_dict[r().rstrip()]
s = r_dict[r().rstrip()]
t = r_dict[r().rstrip()]
print((10*f+s)*(10**t))