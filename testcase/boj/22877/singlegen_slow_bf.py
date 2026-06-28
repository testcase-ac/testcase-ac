import sys

N = 50000
T = 1000000000

write = sys.stdout.write
write(f"{N} {T}\n")
write("R" * (N - 1) + "S\n")
