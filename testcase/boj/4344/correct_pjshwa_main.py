n = int(input())

def round_half_up(number):
  return int(number + 0.5 if number >= 0 else number - 0.5)

import sys
for i in range(n):
  var_it = map(int, sys.stdin.readline().split())
  _n = next(var_it)
  l = sorted(var_it)
  avg = sum(l) / _n
  no = _n
  for j in l:
    if j > avg: break
    no -= 1

  ans = round_half_up(no * 1e5 / _n)
  print(f'{ans / 1e3:.3f}%')
