s, e = map(int, input().split())
if s > e: e, s = s, e 

x, y = map(int, input().split())
x = abs(x)

sr = s % x
t = s + (y - sr)
if t < s: t += x

if y >= x or y < 0 or t > e or t + x <= e: print('Unknwon Number')
else: print(t)
