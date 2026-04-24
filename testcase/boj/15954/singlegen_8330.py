# Valid stress test within constraints to expose floating-point cancellation in the wrong solution.
# N=500, K=500, 499 entries are 999,999 and one entry is 1,000,000 (both within [0, 1e6]).
# This keeps the true variance small (~0.001996) but forces computations around ~1e12 scale.

print("500 500")
arr = [999999]*499 + [1000000]
print(" ".join(map(str, arr)))
