import sys, math
r = sys.stdin.readline

m = int(r())
n = int(r())

square_list = []
for i in range(int(math.sqrt(m)), int(math.sqrt(n)) + 1):
    if i ** 2 < m: continue
    elif i ** 2 > n: break
    square_list.append(i ** 2)
    
if square_list:
    print(sum(square_list))
    print(min(square_list))
else:
    print("-1")