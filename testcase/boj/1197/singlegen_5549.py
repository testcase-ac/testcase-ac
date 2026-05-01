# Generate a maximum-size test for the MST problem:
# V = 10 000 nodes, E = 100 000 edges.
# We build a “spine” of V−1 edges with moderately large negative weights
# so that the MST weight stays ≥ −2^31,
# and fill up the rest with heavy positive edges that will never be chosen.

V = 10_000
E = 100_000
print(V, E)

# 1) Build a simple chain 1–2–3–...–V with weight = −200 000
#    MST will include all these edges; total weight = −(V−1)*200000 ≈ −1.9998e9
for i in range(1, V):
    print(i, i+1, -200000)

# 2) Add (E−(V−1)) extra edges of very large positive weight (1 000 000)
#    so they are never picked by a correct MST algorithm.
for _ in range(E - (V - 1)):
    print(1, V, 1000000)
