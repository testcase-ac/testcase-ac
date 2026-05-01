# Generate a maximum‐size test for n = 100000 points.
# We stay within |x|,|y| ≤ 10000 and produce exactly 100000 points.
# This is simple, large, and stresses any O(n log n) vs O(n^2) solutions.
n = 100000
print(n)
# Use 10 distinct y‐levels and 10000 distinct x‐coordinates → 10000*10 = 100000
for x in range(-5000, 5000):
    for y in range(10):
        print(x, y)
