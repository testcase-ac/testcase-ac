import sys
from math import gcd

MAXV = 2000
BIAS = 1000

def solve():
  t = int(sys.stdin.readline())
  out = []

  for _ in range(t):
    T, S = sys.stdin.readline().split()
    T = int(T)

    Z = len(S)
    i = 0
    f = 1

    rolls = []
    mod = 0

    # Parse expression
    while i < Z:
      token = ""
      while i < Z and S[i] not in "+-":
        token += S[i]
        i += 1

      if len(token) > 1 and token[1] == 'd':
        cnt = int(token[0])
        side = int(token[2:])
        for _ in range(cnt):
          rolls.append((f, side))
      else:
        mod += f * int(token)

      if i == Z:
        break

      f = 1 if S[i] == '+' else -1
      i += 1

    Rz = len(rolls)
    den = 1

    # dp[i][v] = number of ways after i rolls to reach value v
    dp = [[0] * (MAXV + 1) for _ in range(Rz + 1)]
    dp[0][BIAS] = 1

    for i in range(1, Rz + 1):
      f, side = rolls[i - 1]
      for v in range(MAXV + 1):
        if dp[i - 1][v] == 0:
          continue
        for a in range(1, side + 1):
          nv = v + f * a
          if 0 <= nv <= MAXV:
            dp[i][nv] += dp[i - 1][v]
      den *= side

    # Debug output (same as C++)
    # out.append("dp = ")
    # for v in range(MAXV + 1):
    #   if dp[Rz][v] > 0:
    #     out.append(f"  {v - BIAS}: {dp[Rz][v]}/{den}")

    T += BIAS - mod
    total = sum(dp[Rz][v] for v in range(T, MAXV + 1) if v >= 0)

    if total == 0:
      out.append("0")
    else:
      g = gcd(total, den)
      if den == g:
        out.append("1")
      else:
        out.append(f"{total // g}/{den // g}")

  print("\n".join(out))


if __name__ == "__main__":
  solve()
