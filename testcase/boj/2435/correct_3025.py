n, k = map(int, input().split())
l = list(map(int, input().split()))
print(max(sum(l[i:i+k]) for i in range(n-k+1)))
