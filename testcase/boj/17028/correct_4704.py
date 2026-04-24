def f():
    n = int(input())
    a = list(map(int, input().split()))
    for i in range(len(a)-2, -1, -1):
        if a[i] > a[i+1]:
            print(i+1)
            return
    print(0)

f()
