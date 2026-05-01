# Generate a maximal testcase for N=100000 points,
# with points in exactly reverse-sorted order by (y, then x).
N = 100000
print(N)
for y in range(100000, 0, -1):
    # x is fixed at its maximum; y goes from 100000 down to 1
    print(100000, y)
