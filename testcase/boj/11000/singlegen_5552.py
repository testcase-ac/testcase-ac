# Maximum testcase generator for the lecture‐room assignment problem
# N = 200 000, all intervals fully overlap to force answer = 200 000

N = 200_000
print(N)
for _ in range(N):
    # 0 ≤ S < T ≤ 10^9
    print(0, 10**9)
