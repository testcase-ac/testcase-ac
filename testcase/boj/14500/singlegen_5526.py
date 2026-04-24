# Generate a maximum-size test for the tetromino problem:
# N = M = 500, all cell values = 1000 (the maximum allowed).
N = M = 500
print(N, M)
row = " ".join(["1000"] * M)
for _ in range(N):
    print(row)
