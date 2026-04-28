def watchable(i, j, A):
  if i == j: return False
  if i > j: i, j = j, i

  slope = (A[j] - A[i]) / (j - i)
  for k in range(i + 1, j):
    if slope * (k - i) + A[i] <= A[k]: return False
  return True

def P5(A):
  mx = 0
  for i in range(len(A)):
    score = 0
    for j in range(len(A)):
      if watchable(i, j, A): score += 1
    mx = max(mx, score)
  return mx

############### SUBMIT THE CODE ABOVE ONLY ###############

# print(P5([1,2])) # 1
# print(P5([1,2,3,4])) # 2
# print(P5([1,11,21,31])) # 2
# print(P5([1,38,75,113])) # 3
# print(P5([1,3,2])) # 2
