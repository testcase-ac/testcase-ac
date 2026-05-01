# This test stresses the quadratic nested loops in the wrong solution, causing TLE.
# N is large, array elements are all 1, and S is larger than the total sum,
# so no subarray meets the requirement and the inner loop runs fully for each i.

n = 99999
s = 100000000
print(f"{n} {s}")
print(" ".join(["1"] * n))
