import sys
r=sys.stdin.readline;a=0;b=0
l=r().rstrip()
ll=[x[0] for x in l.split('|')]
last=l[-1]
for n in ll:
    if n in 'ADE': a+=1
    elif n in 'CFG': b+=1
if a==b:
    if last in 'ADE': print("A-minor")
    elif last in 'CFG': print("C-major")
else:
    if a>b: print("A-minor")
    else:print("C-major")