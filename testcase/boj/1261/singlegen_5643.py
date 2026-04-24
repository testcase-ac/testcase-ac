# Generate maximum-size maze (100×100) with walls everywhere except start/end,
# so the solver must break the maximum number of walls (198) along the shortest path.
M, N = 100, 100
print(M, N)
# build grid full of walls ('1')
grid = [['1']*M for _ in range(N)]
# make start (1,1) and end (N,M) empty
grid[0][0] = '0'
grid[N-1][M-1] = '0'
# print the maze
for row in grid:
    print(''.join(row))
