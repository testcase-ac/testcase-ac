from collections import deque

n = int(input())
c = list(map(int, input().split()))
queue = deque([])
back_edge_starts = []
back_edge_ends = []
for i in range(1, n-1):
    diff = c[i] - c[i-1]
    if diff == 2:
        back_edge_ends.append(i)
        continue
    queue.append(i)
    if diff == -2:
        back_edge_starts.append(i)
queue.append(n-1)
p = [-1] * n
j = 0
p[0] = 0
for i in range(1, n):
    if j < len(back_edge_starts) and p[i-1] == back_edge_starts[j]:
        p[i] = back_edge_ends[j]
        j += 1
    else:
        p[i] = queue.popleft()

p = [x + 1 for x in p]  # Convert to 1-based index
print(' '.join(map(str, p)))
