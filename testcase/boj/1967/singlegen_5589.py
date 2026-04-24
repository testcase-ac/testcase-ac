# Generate a maximum-size tree (n = 10000) forming a single chain with max edge weight (100)
n = 10000
print(n)
for i in range(1, n):
    # parent = i, child = i+1, weight = 100
    print(i, i+1, 100)
