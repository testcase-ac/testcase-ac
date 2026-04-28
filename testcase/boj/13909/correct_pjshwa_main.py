import sys, math
r = sys.stdin.readline

n = int(r())
prime_chae = [True] * (n + 1)

# primes
prime_chae[0] = False
prime_chae[1] = False
for i in range(int(math.sqrt(n))+1):
	idx = 2
	if prime_chae[i]:
		while(i * idx <= n):
			prime_chae[i * idx] = False
			idx += 1

def breakdown(number):
	for i in range(2, n+1):
		if prime_chae[i]:
			current_prime_division = 0
			while number % i == 0:
				number //= i
				current_prime_division += 1
			if current_prime_division % 2: return False
	return True

for i in range(1, n+1):
	print(breakdown(i))

print(true_items)