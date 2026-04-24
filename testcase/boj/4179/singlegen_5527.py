# Generate a maximum-size testcase for Jihun and Fire (R, C ≤ 1000)
R, C = 1000, 1000
print(R, C)
# Initialize an empty maze of dots
grid = [['.'] * C for _ in range(R)]
# Place Jihun roughly in the center
grid[R//2][C//2] = 'J'
# Place a single fire source in one corner
grid[0][0] = 'F'
# Output the maze
for row in grid:
    print(''.join(row))
