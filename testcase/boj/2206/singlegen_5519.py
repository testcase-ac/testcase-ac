# Maximum testcase for N=1000, M=1000 with no walls:
# - largest allowed dimensions
# - simple structure (all 0's)
# - forces BFS to explore the entire grid
N = 1000
M = 1000
print(N, M)
row = '0' * M
for _ in range(N):
    print(row)
