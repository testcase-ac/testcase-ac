import sys

write = sys.stdout.write
write("1\n")
write("1000 1000\n")
row = "1000000 1000" + " 1000" * 1000
for _ in range(1000):
    write(row + "\n")
