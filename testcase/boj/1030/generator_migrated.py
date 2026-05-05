import random
ranset = random.randint
ransam = random.sample

Type = ranset(1, 4)
S, N, K, R1, R2, C1, C2 = 0, 0, 0, 0, 0, 0, 0

if Type <= 3 :
  S = ranset(1, 3)
else :
  S = ranset(0, 10)

N = ranset(3, 8)
while N%2 != K%2 or K == 0 :
  K = ranset(1, N-2)
MR = ranset(0, N**S-1)
R1 = ranset(max(0, MR-24), MR)
R2 = ranset(MR, min(N**S-1, MR+25))
MC = ranset(0, N**S-1)
C1 = ranset(max(0, MC-24), MC)
C2 = ranset(MC, min(N**S-1, MC+25))
print(S, N, K, R1, R2, C1, C2)
