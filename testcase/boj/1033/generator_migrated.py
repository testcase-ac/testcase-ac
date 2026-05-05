import random
import sys

if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))

ranset = random.randint
ransam = random.sample

Type = ranset(1, 4)
N = 0

if Type <= 3 :
  N = ranset(3, 4)
else :
  N = ranset(2, 10)
print(N)

List = [[0]*4 for i in range(N-1)]
Visited = [False]*(N)

for i in range(N-1) :
  Start = ranset(1, N-i-1)
  End = Start
  if i == 0 :
    while End == Start :
      End = ranset(1, N)
    List[i][0] = Start-1
    List[i][1] = End-1
    Visited[Start-1] = True
    Visited[End-1] = True
  else :
    End = ranset(1, i+1)
    SEChange = ranset(0, 1)
    Startstan, Endstan = 0, 0
    Startnum, Endnum = 0, 0
    for j in range(N) :
      if Visited[j] :
        Endstan += 1
        if Endstan == End :
          Endnum = j
      else :
        Startstan += 1
        if Startstan == Start :
          Startnum = j
    if SEChange == 1 :
      Startnum, Endnum = Endnum, Startnum
    List[i][0] = Startnum
    List[i][1] = Endnum
    Visited[Startnum] = True
    Visited[Endnum] = True
  List[i][2] = ranset(1, 9)
  List[i][3] = ranset(1, 9)

Order = ransam(range(0, N-1), N-1)
for i in range(N-1) :
  for j in range(4) :
    print(List[Order[i]][j], end=" ")
  print()
