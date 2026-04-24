# Generate a 100×100 map with two 1×1 islands in opposite corners,
# giving the maximum possible shortest‐bridge length (198–1 = 197).
N = 100
print(N)
for i in range(N):
    row = ["0"] * N
    if i == 0:
        row[0] = "1"
    if i == N - 1:
        row[N - 1] = "1"
    print(" ".join(row))
