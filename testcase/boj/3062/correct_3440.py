n = int(input())
for i in range(n):
    t = input()
    r = t[::-1]
    k = str(int(t) + int(r))
    print('YES' if k == k[::-1] else 'NO')

