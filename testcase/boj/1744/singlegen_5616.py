# Generate a maximal test case for N < 50 with a wide variety of values
N = 49
nums = []
# 15 large positives
nums += list(range(1000, 985, -1))      # 1000, 999, ..., 986
# 15 large negatives
nums += list(range(-1000, -985, 1))     # -1000, -999, ..., -986
# Some ones (should be added directly, not paired)
nums += [1] * 5
# Some zeros (to potentially neutralize an unpaired negative)
nums += [0] * 4
# A few small positives and negatives
nums += [2, 3, 4, 5, -2, -3, -4, -5, 1, 0]
assert len(nums) == N

print(N)
for x in nums:
    print(x)
