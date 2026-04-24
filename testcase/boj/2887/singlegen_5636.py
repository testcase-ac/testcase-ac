# Generate a maximum-size test with N = 100000 planets.
# We assign simple but distinct coordinates within [-1e9,1e9].
N = 100000
print(N)
for i in range(N):
    # x ranges from 0 to N-1
    # y ranges from N to 2N-1
    # z ranges from 2N to 3N-1
    # All are well within the coordinate limits.
    print(i, i + N, i + 2 * N)
