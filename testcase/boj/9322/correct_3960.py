T = int(input())
for _ in range(T):
    n = int(input())
    f = input().split()
    s = input().split()
    mp = {k: i for i, k in enumerate(f)}
    ans = ['' for i in range(n)]
    for a, b in zip(s, input().split()):
        ans[mp[a]] = b
    print(' '.join(ans))
