MX = 10**6+1
sieve = [False for i in range(MX)]
pr = []
for i in range(2, MX):
	if not sieve[i]:
		pr.append(i)
		if i*i <= MX:
			for j in range(i*2, MX, i):
				sieve[j] = True
p, k = map(int, input().split())

for i in pr:
	if i >= k:
		break
	if p % i == 0:
		print('BAD', i)
		exit(0)
print('GOOD')
