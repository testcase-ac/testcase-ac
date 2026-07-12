# Generates a maximal test for:
# N up to 10^6, M up to 10^3, and 0 ≤ A_i ≤ 10^9.
# We use N=10^6, M=1000, and all A_i = 0
# (this produces the largest possible number of divisible subarrays
# and tests 64-bit accumulation).
import sys

N = 10**6
M = 1000
sys.stdout.write(f"{N} {M}\n")
# Print exactly N zeros without trailing whitespace.
sys.stdout.write(" ".join(["0"] * N))
sys.stdout.write("\n")
