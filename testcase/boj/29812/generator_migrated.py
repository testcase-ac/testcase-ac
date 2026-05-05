import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint

HYU = ['H', 'Y', 'U']
Type = ranset(0, 20)
N, D, M = 0, 0, 0
if Type%7 <= 5 :
  N = ranset(1, 15)
  D = ranset(1, 8)
  M = ranset(1, 8)
else :
  N = ranset(1, 200000)
  D = ranset(1, 100)
  M = ranset(1, 100)
print(N)
for i in range(N) :
  isHYU = ranset(1, 8)
  if Type/7 == 0 :
    if isHYU <= 3 :
      letter = ranset(65, 90)
      print(chr(letter), end="")
    elif isHYU <= 6:
      letter = ranset(97, 122)
      print(chr(letter), end="")
    else :
      letter = ranset(0, 2)
      print(HYU[letter], end="")
  else :
    if isHYU <= 1 :
      letter = ranset(65, 90)
      print(chr(letter), end="")
    elif isHYU <= 2 :
      letter = ranset(97, 122)
      print(chr(letter), end="")
    else :
      letter = ranset(0, 2)
      print(HYU[letter], end="")
print()
print(D, M)
