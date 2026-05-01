# Generate the maximum test for BOJ 9012-like VPS checker:
# T should be as large as allowed (here assumed 50), and each string as long as allowed (50 chars).
T = 50
print(T)
# A valid VPS of length 50
valid = "()" * 25
# An invalid VPS of length 50 (unbalanced: 26 '(' and only 24 ')')
invalid = "(" * 26 + ")" * 24
for i in range(T):
    # Alternate valid and invalid to cover both cases
    print(valid if i % 2 == 0 else invalid)
