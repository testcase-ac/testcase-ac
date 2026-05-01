# Generate a maximum-size test for the “빙산” problem:
# N, M = 300 (max). Fill a 100×100 block inside with height=10 (so exactly 10,000 ice cells),
# the rest zeros. Border rows/cols remain zero as required.

N = M = 300
print(N, M)
for i in range(N):
    row = []
    for j in range(M):
        # place a 100x100 block of ice of height 10 at rows 1..100, cols 1..100
        if 1 <= i <= 100 and 1 <= j <= 100:
            row.append("10")
        else:
            row.append("0")
    print(" ".join(row))
