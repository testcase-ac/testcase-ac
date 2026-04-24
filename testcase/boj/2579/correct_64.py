N = int(input())
p = [0]
for _ in range(N):
    p.append(int(input()))
if N == 1:
    print(p[1])
    exit(0)
dp = [0, p[1], p[1] + p[2]]
for i in range(3, N+1):
    dp.append(max(dp[i-3] + p[i-1] + p[i], dp[i-2] + p[i]))
print(dp[N])
