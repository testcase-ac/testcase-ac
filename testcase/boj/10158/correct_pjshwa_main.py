w, h = map(int, input().split())
p, q = map(int, input().split())
t = int(input())

x = (p + t) % (2 * w)
y = (q + t) % (2 * h)

x = min(x, 2 * w - x)
y = min(y, 2 * h - y)
print(f'{x} {y}')
