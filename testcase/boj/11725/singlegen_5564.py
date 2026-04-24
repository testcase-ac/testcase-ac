# Maximum test case for “find parent in a tree” problem
# Constructs a simple chain of length N = 100000:
# 1–2, 2–3, 3–4, …, 99999–100000

N = 100000
print(N)
for i in range(1, N):
    print(i, i + 1)
