# Generate a 64×64 checkerboard so that every quadtree node is mixed,
# forcing the compressor to subdivide down to 1×1 pixels everywhere.
N = 64
print(N)
for i in range(N):
    # alternate 0/1 each cell, offset by row to form a true checkerboard
    print(''.join('0' if (i + j) % 2 == 0 else '1' for j in range(N)))
