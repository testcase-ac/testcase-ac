import sys

N = 1000000

write = sys.stdout.write
write(f"{N}\n")
write(" ".join(str(i) for i in range(N, 0, -1)) + "\n")
