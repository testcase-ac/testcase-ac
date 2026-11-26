vertices = 20_000
hub = vertices - 1
repeats = 25_000
weights = range(1, 11)

# The shortcuts queue longer paths before the chain improves them.
# Many outgoing edges from the hub make unnecessary scans expensive.
print(vertices, 2 * (hub - 2) + 1 + repeats * len(weights))
print(1)
for vertex in range(1, hub - 1):
    print(vertex, vertex + 2, 10)
    print(vertex, vertex + 1, 1)
print(hub - 1, hub, 1)
for _ in range(repeats):
    for weight in weights:
        print(hub, vertices, weight)
