import sys

n = int(input())

def bfs(point):
  global k
  visit_list = [-1] * 1000001
  points_queue = [(-1, point, 0)]
  hist = []
  lim = lambda x: 1 <= x <= 1000000
  def next_point_f(p):
    if p % 3 == 0:
      yield p // 3
    if p % 2 == 0:
      yield p // 2
    yield p - 1
  while True:
    prev_point, current_point, current_iteration = points_queue.pop(0)

    if current_point == 1:
      cp = 1
      pp = prev_point
      while pp != -1:
        hist.append(cp)
        cp = pp
        pp = visit_list[cp]

      hist.append(point)
      break

    if visit_list[current_point] != -1 or not lim(current_point): continue
    visit_list[current_point] = prev_point

    for next_point in next_point_f(current_point):
      if lim(next_point) and visit_list[next_point] == -1: points_queue.append((current_point, next_point, current_iteration + 1))
  return current_iteration, hist

ans, hist = bfs(n)
print(ans)
for el in reversed(hist):
  print(el, end = ' ')
