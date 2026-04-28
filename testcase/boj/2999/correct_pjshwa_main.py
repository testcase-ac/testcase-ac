import sys
r = sys.stdin.readline

i = 0
msg = r().rstrip()
l = len(msg)
max_r = 0
while i <= 10:
    i += 1
    if l % i != 0: continue
    if i > l // i: break
    max_r = i

c = l // max_r
for i in range(max_r):
    for j in range(c):
        print(msg[i + max_r * j], end="")