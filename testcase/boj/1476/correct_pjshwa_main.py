import sys
r = sys.stdin.readline
e, s, m = map(int, r().split())

pl = [28*i+s for i in range(285)]
e_filter = lambda x: x % 15 == e % 15
m_filter = lambda x: x % 19 == m % 19
print(next(filter(e_filter, filter(m_filter, pl))))