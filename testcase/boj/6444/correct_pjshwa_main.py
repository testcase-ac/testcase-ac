import sys, re, heapq; r = sys.stdin.readline
t = int(r())

# 'A' -> 1, 'AA' -> 27, ...
def alpha_to_num(alpha):
  sz = len(alpha)
  ans = 0
  for i in range(sz):
    ans += (26 ** (sz - i - 1))
    ans += (ord(alpha[i]) - 65) * (26 ** (sz - i - 1))
  return ans

for _ in range(t):
  m, n = map(int, r().split())
  graph = {}
  answer = [0 for _ in range(m * n)]
  indegree = [0 for _ in range(m * n)]
  heap = []

  for i in range(n):
    values = r().rstrip().split()
    for j, val in enumerate(values):
      if val[0] == '=':
        sz = len(val)
        for cn in val[1:sz].split('+'):
          ci = int(re.search('\d+', cn)[0]) - 1
          cj = int(alpha_to_num(re.search('[A-Z]+', cn)[0])) - 1
          indegree[i * m + j] += 1
          idx = ci * m + cj
          if idx not in graph: graph[idx] = []
          graph[idx].append(i * m + j)
      else:
        answer[i * m + j] += int(val)

  for i in range(m * n):
    if indegree[i] == 0: heapq.heappush(heap, i)

  for _ in range(m * n):
    idx = heapq.heappop(heap)
    if idx not in graph: continue

    for nidx in graph[idx]:
      answer[nidx] += answer[idx]
      indegree[nidx] -= 1
      if indegree[nidx] == 0: heapq.heappush(heap, nidx)

  for i in range(n):
    print(' '.join(map(str, (answer[i * m + j] for j in range(m)))))
