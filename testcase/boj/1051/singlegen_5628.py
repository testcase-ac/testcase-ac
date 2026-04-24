# Maximum testcase for N, M ≤ 50 with the largest possible square (50×50 ⇒ area = 2500).
N = M = 50
print(N, M)
# Fill every cell with the same digit so that the corners of the whole grid match
for _ in range(N):
    print('7' * M)
