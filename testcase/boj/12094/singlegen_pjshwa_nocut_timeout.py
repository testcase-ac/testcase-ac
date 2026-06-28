import sys

N = 20

write = sys.stdout.write
write(f"{N}\n")
row = " ".join(["2"] * N)
for _ in range(N):
    write(row + "\n")
