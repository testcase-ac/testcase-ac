# Generate a maximum test case for the 4-sum zero problem:
# n = 4000 (the largest allowed),
# all entries zero so that every quadruple sums to 0,
# yielding n^4 = 4000^4 = 2.56e14 total solutions.
n = 4000
print(n)
for _ in range(n):
    print("0 0 0 0")
