# Generate a worst‐case 50×50 test where the greedy algorithm
# must flip every possible 3×3 block (48×48 = 2304 flips).
N, M = 50, 50

# Start A as all zeros
A = [[0]*M for _ in range(N)]

# Build B by flipping every 3×3 in row-major order
B = [row[:] for row in A]
for i in range(N-2):
    for j in range(M-2):
        for di in range(3):
            for dj in range(3):
                B[i+di][j+dj] ^= 1

# Output the test case
print(N, M)
for row in A:
    print(''.join(map(str, row)))
for row in B:
    print(''.join(map(str, row)))
