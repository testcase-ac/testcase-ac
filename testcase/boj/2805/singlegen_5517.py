# Generate a maximum test case for the wood‐cutting problem:
# N = 1_000_000 (max), M = 2_000_000_000 (max), all tree heights = 1_000_000_000 (max)
import sys

N = 10**6
M = 2 * 10**9
sys.stdout.write(f"{N} {M}\n")
# print N heights of 10^9 separated by spaces
for _ in range(N):
    sys.stdout.write("1000000000 ")
