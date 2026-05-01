# Generates a case that triggers integer overflow in the wrong solution.
# N=100000 and the sequence uses values 1..99999 then 1, avoiding OOB but causing the
# count of unique subarrays to exceed 32-bit int range.

n = 100000
print(n)
# Sequence: 1 2 3 ... 99999 1
# This stays within [1..99999] so the buggy visited array (size N) doesn't go out of bounds,
# but the total count exceeds INT32_MAX, causing overflow in the wrong solution.
print(" ".join([str(i) for i in range(1, 100000)] + ["1"]))
