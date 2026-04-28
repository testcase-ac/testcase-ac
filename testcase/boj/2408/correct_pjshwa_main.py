n = int(input())
works = []
for _ in range(2*n-1):
    works.append(input().rstrip())
print(eval(''.join(works)))