Al, As, Ae = map(int, input().split())
Bl, Bs, Be = map(int, input().split())
Cl, Cs, Ce = map(int, input().split())
r, l = float('inf'), Al * Bl * Cl

for i in range(Bl * Cl + 1):
  k = i * Al + As
  b, c = k % Bl, k % Cl
  if Bs <= b and b <= Be and Cs <= c and c <= Ce: r = min(r, k)

for i in range(Al * Cl + 1):
  k = i * Bl + Bs
  a, c = k % Al, k % Cl
  if As <= a and a <= Ae and Cs <= c and c <= Ce: r = min(r, k)

for i in range(Al * Bl + 1):
  k = i * Cl + Cs
  a, b = k % Al, k % Bl
  if As <= a and a <= Ae and Bs <= b and b <= Be: r = min(r, k)

if r == float('inf'): print(-1)
else: print(r)
