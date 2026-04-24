import sys

def input(): return sys.stdin.readline().rstrip()

n, m = map(int, input().split())

st = set()
for _ in range(int(n)):
    s = input()
    for i in range(1, len(s) + 1):
        st.add(s[:i])

ans = 0
for i in range(int(m)):
    s = input()
    if s in st:
        ans += 1
print(ans)
