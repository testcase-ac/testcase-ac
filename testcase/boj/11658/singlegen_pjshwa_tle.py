import sys

N = 1024
M = 100000

write = sys.stdout.write
write(f"{N} {M}\n")
row = " ".join(["1"] * N)
for _ in range(N):
    write(row + "\n")
for _ in range(M):
    write("1 2 2 1023 1023\n")
