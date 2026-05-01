# Generate a maximum test case for N=100000 points, in reverse-sorted order
N = 100000
print(N)
# Points (x, y) will both range from 100000 down to 1, so input is in worst-case reverse sorted
for x in range(100000, 0, -1):
    print(x, x)
