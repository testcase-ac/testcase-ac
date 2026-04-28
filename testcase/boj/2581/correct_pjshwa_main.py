m = int(input())
n = int(input())

import math
chae = [True for i in range(n+1)]

chae[0] = False
chae[1] = False

for index, item in enumerate(chae):
	if index > math.sqrt(n): break
	if item:
		i = 2
		while(i * index <= n):
			chae[i*index] = False
			i += 1
			
primes_list = []
for i in range(m, n+1):
	if chae[i]: primes_list.append(i)

if primes_list:
	print(sum(primes_list))
	print(min(primes_list))
else:
	print(-1)