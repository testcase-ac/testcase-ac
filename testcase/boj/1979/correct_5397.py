n, k = map(int, input().split())
if n == 1:
    print(k)
    exit(0)

for i in range(1, 60):
    p10 = 10 ** i
    p = k * p10 - n * k
    q = 10 * n - 1
    if p % q == 0 and p // q < p10 and p // q >= p10 // 10:
        print(p // q, k, sep='')
        exit(0)

print(0)
