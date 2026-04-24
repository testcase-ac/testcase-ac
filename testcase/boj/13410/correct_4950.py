n, k = map(int, input().split())
print(max(int(str((i+1)*n)[::-1]) for i in range(k)))
