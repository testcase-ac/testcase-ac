import sys
from itertools import count
for i in count(1):
    a,op,c = input().split()
    if op == 'E':
        exit(0)
    ok = 'true' if eval(a+op+c) else 'false'
    print('Case %d: %s' % (i, ok))
