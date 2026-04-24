a = int(input())
k = []
p = 0
for i in range(a):
    b = [int(x) for x in input().split()]
    c = b[0]
    total = sum(b)-c
    avg = total/c
    del b[0]
    b.sort()
    for j in b:
        if j <= avg:
            p += 1
        else:
            break
    k.extend([(1-(p/c))*100])
    p = 0
for g in k:
    print('%0.3f%%' % g)
