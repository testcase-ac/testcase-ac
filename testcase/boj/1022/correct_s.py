r1, c1, r2, c2 = map(int, input().split())
rows = r2 - r1 + 1
cols = c2 - c1 + 1

sign = lambda x: 1 - 2 * (x < 0)

def get_number(r, c):
  m, d = max(abs(r), abs(c)), sign(r - c)
  return 1 + 4 * m * m + d * (2 * m + r + c)

numlen = len(str(max(
  get_number(r1, c1), 
  get_number(r2, c1), 
  get_number(r2, c2),
)))

fmt = f'%{numlen}d'

for i in range(r1, r2 + 1):
  print(' '.join(fmt % get_number(i, j) for j in range(c1, c2 + 1)))