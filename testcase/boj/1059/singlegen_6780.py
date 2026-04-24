# Generates a maximal test case for the problem:
# L = 50, S = {1,2,...,49,1000}, n = 525
# This makes the largest possible "gap" [50..999] containing n=525,
# yielding on the order of (525-49)*(1000-525)-1 = 226099 good intervals.
L = 50
S = list(range(1, 50)) + [1000]
n = 525

print(L)
print(*S)
print(n)
