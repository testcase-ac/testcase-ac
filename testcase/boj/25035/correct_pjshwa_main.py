ga, lx = None, None
d = [[None for _ in range(201)] for _ in range(201)]

def r(x, v):
  if x >= lx: return False
  if d[x][v] != None: return d[x][v]

  r1 = r(x + 2 * v, v)
  r2 = r(x + 2 * v + ga, v + ga)
  res = not (r1 and r2)
  d[x][v] = res
  return res

def ALSDJFKSND(x, v, a):
  global ga, lx
  ga, lx = a, 2 * x

  for i in range(201):
    for j in range(201): d[i][j] = None

  # Alice pressed 'A'
  r1 = not r(4 * v, v)

  # Alice pressed 'B'
  r2 = not r(4 * v + a, v + a)

  if r1:
    if r2: return 'C'
    else: return 'A'
  else:
    if r2: return 'B'
    else: return 'D'

######### SUBMIT THE ABOVE CODE ONLY #########

# print(ALSDJFKSND(3,2,1)) # C
# print(ALSDJFKSND(34,5,6)) # B
# print(ALSDJFKSND(38,4,7)) # D
# print(ALSDJFKSND(90,2,9)) # A
