# Generate a maximum test case for "Two Solutions" problem.
# N = 100,000 (max)
# Values range symmetrically at extremes to test overflow and two-pointer logic:
#   negatives from -1e9 up to -1e9+49999,
#   positives from  1e9-49999 up to  1e9.
# Closest sum to zero is -1e9+49999 + (1e9-49999) = 0.
N = 100000
print(N)
# print negatives: -1000000000, -999999999, ..., -1000000000+49999
for i in range(50000):
    val = -1000000000 + i
    print(val, end=' ')
# print positives:  999950001,  999950002, ..., 1000000000
for i in range(50000):
    val = 1000000000 - 49999 + i
    print(val, end=' ')
print()
