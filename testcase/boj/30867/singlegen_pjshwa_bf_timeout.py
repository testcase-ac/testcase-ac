import sys

L = 200000
N = 200000

write = sys.stdout.write
write(f"{L} {N}\n")
write("w" * (L // 2) + "h" * (L // 2) + "\n")
