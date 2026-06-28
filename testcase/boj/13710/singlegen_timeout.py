import sys

N = 100000

write = sys.stdout.write
write(f"{N}\n")
write(" ".join(["0"] * N) + "\n")
