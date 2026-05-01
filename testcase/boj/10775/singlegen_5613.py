# Generate a maximal test for G, P up to 1e5.
# We set G = 100000, P = 100000 and use every gate exactly once,
# arriving in descending order so DSU has to link from high to low.
G = 10**5
P = 10**5
print(G)
print(P)
for i in range(G, 0, -1):
    print(i)
