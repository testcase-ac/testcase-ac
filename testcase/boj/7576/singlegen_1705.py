C, R = 1000, 1000
print(C, R)
for r in range(R):
  print(' '.join(('1' if r == 0 and c == 0 else '0') for c in range(C)))
