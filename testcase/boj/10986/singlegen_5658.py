# Generates a maximal test for:
# N up to 10^6, M up to 10^3, and 0 ≤ A_i ≤ 10^9.
# We use N=10^6, M=1000, and all A_i = 0
# (this produces the largest possible number of divisible subarrays
# and tests 64-bit accumulation).
import sys

N = 10**6
M = 1000
sys.stdout.write(f"{N} {M}\n")
# print N zeros separated by spaces
chunk = "0 " * 1000
for _ in range(N // 1000):
    sys.stdout.write(chunk)
# if N is not a multiple of 1000 (not in this case), you'd handle remainder here
