def divisorGenerator(n):
    large_divisors = []
    for i in range(1, int(n**0.5 + 1)):
        if n % i == 0:
            yield i
            if i*i != n:
                large_divisors.append(n // i)
    for divisor in reversed(large_divisors):
        yield divisor

import sys
r = sys.stdin.readline

n=int(r())
while n!=-1:
	
	if 2*n==sum(divisorGenerator(n)):
		print("{} = {}".format(n,' + '.join(list(map(str,divisorGenerator(n)))[:-1])))
	else:
		print("{} is NOT perfect.".format(n))
	n=int(r())