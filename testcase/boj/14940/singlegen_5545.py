# Generate a maximal 1000x1000 test case.
# We place the single target (2) at the top‐left corner (0,0).
# We insert a vertical wall at column 500 to split the grid in two:
#   - left half (columns 0..499) is reachable
#   - right half (columns 500..999) is completely unreachable
n, m = 1000, 1000
print(n, m)
for i in range(n):
    row = []
    for j in range(m):
        if i == 0 and j == 0:
            row.append('2')      # The unique target
        elif j == 500:
            row.append('0')      # Impassable wall barrier
        else:
            row.append('1')      # Free cell
    print(' '.join(row))
