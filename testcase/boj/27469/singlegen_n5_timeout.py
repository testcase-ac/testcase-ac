import sys

write = sys.stdout.write
write("100 100 100\n")
row = "." * 100
for _ in range(100):
    write(row + "\n")
write("1 1\n")
write("100 100\n")
