import sys
r = sys.stdin.readline

n, l = map(int, r().split())
locs = list(map(int, r().split()))
locs.sort()

req_tape = 0
covered_to = 0
for loc in locs:
    if loc < covered_to: continue
    req_tape += 1
    covered_to = loc + l

print(req_tape)
