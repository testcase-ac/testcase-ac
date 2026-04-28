import sys
a, p = tuple(map(int, sys.stdin.readline().split()))
def decompose(n):
    s = 0
    while(n != 0):
        s += (n % 10) ** p
        n //= 10
        
    return s

l = [a]

while(True):
	next_num = decompose(l[-1])
	# print(l)
	if next_num in l:
	    print(l.index(next_num))
	    break
	else: l.append(next_num)