def f():
    return ''.join(input().split())

T = int(input())
for i in range(T):
    n, m = map(int, input().split())
    x, y = int(f()), int(f())
    l = f() * 20
    print(sum(1 for z in range(n) if x <= int(l[z:z+m]) <= y))
