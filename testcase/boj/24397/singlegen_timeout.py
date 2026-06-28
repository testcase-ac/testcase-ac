import sys

N = 100000
M = 100000

write = sys.stdout.write
write(f"{N} {M} 1\n")
write(" ".join(["1"] * N) + "\n")
write(" ".join(["1"] * M) + "\n")
