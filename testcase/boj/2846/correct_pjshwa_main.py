import sys
r = sys.stdin.readline

n = int(r())
road = list(map(int, r().split()))

streak = 0
max_streak = 0
for i in range(1, n):
    if road[i] > road[i - 1]:
        streak += (road[i] - road[i - 1])
    else:
        if max_streak < streak: max_streak = streak
        streak = 0

if max_streak < streak: max_streak = streak
print(max_streak)
