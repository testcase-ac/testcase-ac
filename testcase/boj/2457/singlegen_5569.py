# Generate a maximum-size test for the flower‐covering problem.
# We need N ≤ 100000. Each flower must be given by “m1 d1 m2 d2”.
# To cover from 3/1 through 11/30 inclusive, we use end date 12/1,
# so that the bloom interval is [3/1,12/1) (i.e. visible through 11/30).
#
# This input uses N=100000 and every interval covers the entire target range.
# The minimal answer is 1, but the input is as large as allowed.

N = 100000
print(N)
for _ in range(N):
    # start: March 1, end: December 1
    print(3, 1, 12, 1)
