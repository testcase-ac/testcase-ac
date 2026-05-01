# Generate a maximal test for N = 100000 (star-shaped tree + straightforward BFS order)
N = 10**5
print(N)
# Edges: star centered at 1
for i in range(2, N+1):
    print(1, i)
# A valid BFS from node 1 in a star is simply 1,2,3,...,N
print(*range(1, N+1))
