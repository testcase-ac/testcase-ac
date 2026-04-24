a = [0, 1, 1]
n = int(input())
while len(a) <= n:
    a.append(a[-2]+a[-1])
print(a[n])
