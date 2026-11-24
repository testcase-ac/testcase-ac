N = 500
ROUNDS = 250

# Each scan can traverse the reachable negative cycle 250 times,
# decreasing the source distance by 5,000,000 in Bellman-Ford.
print(N, 2 * ROUNDS)
for _ in range(ROUNDS):
    print(1, 2, -10000)
    print(2, 1, -10000)
