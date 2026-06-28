import sys

N = 1000000
K = 500001

write = sys.stdout.write
write(f"{N} {K}\n")
write("1\n")
write(" ".join(["1"] * N) + "\n")
