n = int(input())

for i in range(n):
    s = input().split()
    print(f'Case #{i+1}: ', end='')
    while s:
        print(s.pop(), end=" ")
    print()
