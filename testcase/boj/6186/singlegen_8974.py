# Generates a test case that breaks the wrong solution by exploiting out-of-bounds access
# The bug: when C=100, calling check on a cell at column 99 recurses to x+1=100,
# which accesses a[y][100] and (due to row-major layout) reads a[y+1][0].
# This erroneously merges separate clumps across row boundary.

# We construct:
# R=3, C=100
# Row 0: all dots
# Row 1: a single '#' at column 99
# Row 2: a single '#' at column 0
# Correct answer is 2, but the wrong code will count 1.

print("3 100")
print("." * 100)
print("." * 99 + "#")
print("#" + "." * 99)
