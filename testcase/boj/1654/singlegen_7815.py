# This generator prints a test case for the LAN cable cutting problem (BOJ 1654).
# It targets the bug in the wrong solution where it iterates i <= k, reading one extra
# uninitialized length value, which can corrupt the count and yield an incorrect result.
# The case is crafted so that just 1 extra piece at length=2 would flip the decision.

# K = 10000, N = 1000000
# 9999 cables of length 200 and 1 cable of length 199 => total length = 1,999,999.
# Correct answer should be 1 because sum//2 = 999,999 < N.
# The wrong code erroneously includes length[10000]/2; if that uninitialized value >= 2,
# it will incorrectly allow length 2 and may output 2 instead of 1.

print("10000 1000000")
for _ in range(9999):
    print(200)
print(199)
