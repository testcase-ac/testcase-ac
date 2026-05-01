# Generate a single maximal test case for the "원타곤 침투" problem
# N = 10000 (max number of pairs of regions), W = 10000 (max squad size)
# All regions have exactly W enemies, so no two regions can be paired (forces 2N squads).
N = 10000
W = 10000
print(1)               # T = 1 test case
print(N, W)            # N and W
# First circle regions (1 through N), each with W enemies
print(" ".join(str(W) for _ in range(N)))
# Second circle regions (N+1 through 2N), each with W enemies
print(" ".join(str(W) for _ in range(N)))
