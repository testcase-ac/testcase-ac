# Generate maximum-size test: N = 16, all cells empty (0)
N = 16
print(N)
for _ in range(N):
    print(" ".join(["0"] * N))
