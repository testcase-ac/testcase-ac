# Generates a simple polygon with N=10000 vertices:
# first walk along the bottom edge from (1,0) to (5000,0),
# then back along the top edge from (5000,100000) to (1,100000).
N = 10000
print(N)
# Bottom edge
for x in range(1, 5001):
    print(x, 0)
# Top edge
for x in range(5000, 0, -1):
    print(x, 100000)
