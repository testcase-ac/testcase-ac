self_numbers = [True] * 10001

self_numbers[0] = False

def d(n):
	return n + sum(map(int, list(str(n))))

for i in range(10001):
	if self_numbers[i]:
		n = i
		while(True):
			n = d(n)
			if n > 10000: break
			self_numbers[n] = False

for i, e in enumerate(self_numbers):
	if e: print(i)