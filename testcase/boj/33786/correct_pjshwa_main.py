a = [0] * 1001
for i in range(1, 1001): a[i] = i * (1 + a[i - 1])

n = int(input())
print(a[n])
