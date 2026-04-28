n = int(input())
pos = 1

for _ in range(n):
  a = map(int, input().split())

  oleft = pos <= 13
  if not oleft: pos -= 13

  acc = 0
  tleft = False
  for e in a:
    if not (tleft ^ oleft):
      if pos <= e:
        pos = acc + pos
        break
      else:
        pos -= e
    acc += e
    tleft = not tleft

print(pos)
