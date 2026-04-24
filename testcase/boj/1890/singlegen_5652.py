# Generate a maximal-size test for the N×N jump‐game problem:
# N = 100, all cells “9” (maximum allowed), except the bottom‐right cell which must be 0.
N = 100
print(N)
for i in range(N):
    row = ["9"] * N
    if i == N - 1:
        row[-1] = "0"
    print(" ".join(row))
