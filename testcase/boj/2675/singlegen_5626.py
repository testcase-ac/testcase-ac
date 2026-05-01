# Generate a maximal test for the “문자열 반복” problem:
# T = 1000 (max testcases)
# R = 8 (max repeat)
# |S| = 20 (max length)
T = 1000
S = "ABCDEFGHIJKLMNOPQRST"  # 20 distinct alphanumeric chars
print(T)
for _ in range(T):
    # Each line: max R and max‐length S
    print(8, S)
