# Generate a maximum-size test for the terrain-flattening problem
# N, M = 500 (max), B = 64,000,000 (max)
# Heights are varied in [0..256] by a simple (i+j)%257 pattern.

N, M, B = 500, 500, 64000000
print(N, M, B)
for i in range(N):
    row = [(i + j) % 257 for j in range(M)]
    print(" ".join(map(str, row)))
