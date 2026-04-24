# Generate a maximum-size test (R=C=50) for the hedgehog-flood problem.
# One D at (0,0), one S at (49,49). Water seeds on top row and rightmost column.
# Rocks placed every 3 cells to form a labyrinth.
R, C = 50, 50
print(R, C)
grid = [['.' for _ in range(C)] for _ in range(R)]

# Place beaver's den and hedgehog start
grid[0][0] = 'D'
grid[R-1][C-1] = 'S'

# Seed water on the entire first row (except D) and last column (except S)
for j in range(C):
    if grid[0][j] == '.':
        grid[0][j] = '*'
for i in range(R):
    if grid[i][C-1] == '.':
        grid[i][C-1] = '*'

# Place rocks in a regular pattern to create obstacles
for i in range(R):
    for j in range(C):
        if grid[i][j] == '.' and i % 3 == 2 and j % 3 == 2:
            grid[i][j] = 'X'

# Output the grid
for row in grid:
    print(''.join(row))
