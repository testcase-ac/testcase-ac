n, m = map(int, input().split())
ls = []
for i in range(n):
    a, b = input().split()
    ls.append([a, int(b)])

ls.sort(key=lambda a: -a[1])

ans = []
for a, b in ls:
    if m >= b:
        m -= b
        ans.append(a)

if m > 0:
    print('0')
else:
    print(len(ans))
    print('\n'.join(ans))

