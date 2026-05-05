import random
ranset = random.randint

Type = ranset(0, 19)
N = 0
if Type%5 <= 4 :
  N = ranset(1, 5)
else :
  N = ranset(1, 40)

Lists = [0]*26
len = 0
for i in range(26) :
  Lists[i] = ranset(1, 7)
for i in range(N) :
  if Type//5 <= 2 :
    letter = ranset(65, 67)
  else :
    letter = ranset(65, 90)
  len += Lists[letter-65]+1
  print(chr(letter), end="")
  for i in range(Lists[letter-65]) :
    if Type//5 <= 2 :
      letter1 = ranset(97, 99)
    else :
      letter1 = ranset(97, 122)
    print(chr(letter1), end="")
  NX = ranset(0, 25)
  if Type%5 <= 4 and 20 < len+Lists[NX] :
    break
  elif Type%5 == 0 and 200 < len+Lists[NX] :
    break
