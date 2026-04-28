n = int(input())
s = set()
for i in range(n):
    s.add(input())
l = list(zip(s, map(len, s)))
l.sort(key = lambda x: (x[1], x[0]))
for i in l:
    print(i[0])