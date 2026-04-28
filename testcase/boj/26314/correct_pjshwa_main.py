# T = int(input())
# for s in [input() for _ in range(T)]:
#   s = s.strip()

#   assert 1 <= len(s) <= 20
#   assert s == s.lower()

#   t = sum(map(s.count, 'aeiou'))
#   print(s)
#   print(+ (len(s) < 2*t))


file = [*open(0)]

assert file[-1][-1] == '\n'
dlen = len(file)
plen = int(file[0])
assert plen + 1 <= dlen <= plen + 2

for s in file[1:]:
  s = s.strip()

  if len(s) == 0:
    continue

  assert 1 <= len(s) <= 20

  t = sum(map(s.count, 'aeiou'))
  print(s)
  print(+ (len(s) < 2*t))
