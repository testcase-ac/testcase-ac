n = int(input())
for i in range(n):
    ls = sorted(list(map(int, input().split()))[1:])
    print('Class %d\nMax %d, Min %d, Largest gap %d' % (i+1, ls[-1], ls[0], max(ls[i+1]-ls[i] for i in range(len(ls)-1))))
