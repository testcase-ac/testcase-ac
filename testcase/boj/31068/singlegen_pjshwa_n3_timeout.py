import sys

N = 5000

write = sys.stdout.write
write(f"{N}\n")
write("".join(f"{i} {i}\n" for i in range(1, N + 1)))
