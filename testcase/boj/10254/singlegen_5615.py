# Generate a single test case with n = 200 000 points.
# Two opposite‐corner points at (−1e7,−1e7) and (1e7,1e7) ensure the maximum diameter,
# and the rest of the points lie on the x‐axis in between.
n = 200_000
print(1)        # one test case
print(n)
# farthest‐apart pair
print(-10_000_000, -10_000_000)
print( 10_000_000,  10_000_000)
# fill up the remaining n−2 points along y=0 between x=−1e7 and x=1e7
for i in range(1, n-1):
    x = -10_000_000 + i * 100
    print(x, 0)
