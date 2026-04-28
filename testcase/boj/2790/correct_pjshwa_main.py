import sys
r = sys.stdin.readline

l = []
n = int(r())
for _ in range(n):
    l.append(int(r()))

l.sort()
min_score_to_overcome = 0
for i, x in enumerate(l):
    min_score_to_overcome = max(min_score_to_overcome, x + n - i)

print(len(list(filter(lambda x: x + n >= min_score_to_overcome, l))))
