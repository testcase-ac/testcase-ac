def base_n4(n):
  if n == 0: return '0'
  ans = ''
  while n:
    n, r = divmod(n, -4)
    if r < 0: n += 1; r += 4
    ans = '0123'[r] + ans

  return ans

def P4(x, y):
  xb = base_n4(x)
  yb = base_n4(y * -2)

  sz = max(len(xb), len(yb))
  xb = xb.rjust(sz, '0')
  yb = yb.rjust(sz, '0')
  ans = ''
  for i in range(sz): ans += (xb[i] + yb[i])
  if len(ans) > 2 and ans[0] == '0': ans = ans[1:]

  return ans[:-1] + '.' + ans[-1]
