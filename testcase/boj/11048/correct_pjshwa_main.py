import sys; r = sys.stdin.readline; sys.setrecursionlimit(10**6)
n, m = map(int, r().split())
a = []
dp = []
for i in range(n):
	a.append(list(map(int, r().split())))
	dp.append([-1] * m)

def opt(x, y):
	# print("x: {}, y: {}".format(x, y))
	if x > 0:
		if dp[x-1][y] == -1: dp[x-1][y] = opt(x-1, y)
	if y > 0:
		if dp[x][y-1] == -1: dp[x][y-1] = opt(x, y-1)
	if x > 0:
		if y > 0:
			dp[x][y] = a[x][y] + max(dp[x-1][y], dp[x][y-1])
		else:
			dp[x][y] = a[x][y] + dp[x-1][y]
	else:
		if y > 0:
			dp[x][y] = a[x][y] + dp[x][y-1]
		else:
			dp[x][y] = a[x][y]

	return dp[x][y]

print(opt(n-1, m-1))