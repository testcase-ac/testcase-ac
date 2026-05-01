# Generates the maximum-allowed N = 100000 points in a simple 250×400 grid.
# All points lie within |x|,|y| ≤ 40000 and no three are collinear overall.
# Convex hull size is 4 (the four corners), but the input size is maximal.
N = 100000
print(N)
for x in range(250):
    for y in range(400):
        print(x, y)
