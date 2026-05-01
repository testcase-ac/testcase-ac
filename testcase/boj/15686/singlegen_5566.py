# Generate a maximal test for N=50, M=13, with 13 chicken shops and 100 houses
N, M = 50, 13
print(N, M)
# Initialize empty city
grid = [[0]*N for _ in range(N)]
# Place M=13 chicken shops in the first column, rows 1..13
for k in range(M):
    grid[k][0] = 2
# Place 100 houses (<=2N) in a 10×10 block at bottom-right corner: rows 41..50, cols 41..50
for i in range(10):
    for j in range(10):
        grid[N-10 + i][N-10 + j] = 1
# Output the grid
for row in grid:
    print(" ".join(map(str, row)))
