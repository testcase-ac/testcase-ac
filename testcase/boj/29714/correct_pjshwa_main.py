import sys
r = sys.stdin.readline

by_flavor = {}
n = int(r())
flavors = map(int, r().split())
for f in flavors: by_flavor[f] = by_flavor.get(f, 0) + 1

q = int(r())
for _ in range(q):
  a = list(map(int, r().split()))
  b = list(map(int, r().split()))

  map_a = {}
  for i in range(1, len(a)): map_a[a[i]] = map_a.get(a[i], 0) + 1

  sufficient = True
  for k, v in map_a.items():
    if k not in by_flavor or by_flavor[k] < v: sufficient = False

  if not sufficient: continue

  for k, v in map_a.items(): by_flavor[k] -= v
  for i in range(1, len(b)): by_flavor[b[i]] = by_flavor.get(b[i], 0) + 1

flavors_final = []
for k, v in by_flavor.items():
  for _ in range(v): flavors_final.append(k)

size = len(flavors_final)
print(size)
if size: print(' '.join(map(str, sorted(flavors_final))))
