import sys
r = sys.stdin.readline

n = int(r())

print(n * (n - 1) // 2)
for i in range(n): print(1 << i, end = ' ')
print()
print(n - 1)
for i in range(n): print(i + 1, end = ' ')
print()
