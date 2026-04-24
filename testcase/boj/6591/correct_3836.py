def f(n,k):
	if k > n//2:
		k = n-k
	ret = 1
	for i in range(n-k+1, n+1):
		ret *= i
	for i in range(2, k+1):
		ret //= i
	return ret

while True:
	n, k = map(int, input().split())
	if not n and not k:
		break
	print(f(n,k))
