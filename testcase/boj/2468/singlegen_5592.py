# Maximum testcase for BOJ 2468 “안전 영역”
# N = 100, heights alternate 1 and 2 in a checkerboard pattern.
# At rain height = 1, every cell with height = 2 is an isolated safe area,
# yielding 5000 disconnected regions (the theoretical maximum for N=100).

N = 100
print(N)
for i in range(N):
    row = []
    for j in range(N):
        # Checkerboard: cells with (i+j)%2 == 1 are high ground (2), others low (1)
        row.append('2' if (i + j) % 2 else '1')
    print(' '.join(row))
