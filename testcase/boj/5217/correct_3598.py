T = int(input())
for _ in range(T):
    n = int(input())
    ls = []
    for i in range(1, (n+1)//2):
        ls.append('%d %d' % (i, n-i))
    print('Pairs for %d: %s' % (n, ', '.join(ls)))
