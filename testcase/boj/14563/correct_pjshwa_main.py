import sys, math; r = sys.stdin.readline

input()
numbers = list(map(int, r().split()))

def number_decide(num):
	limit = int(math.sqrt(num))
	index = 1
	divisors = set()
	while index <= limit:
		if num % index == 0:
			divisors.add(index)
			divisors.add(num // index)
		index += 1

	divisors_sum = sum(divisors)
	if divisors_sum == 2 * num: return 0
	elif divisors_sum < 2 * num: return 1
	else: return 2

for number in numbers:
	result = number_decide(number)
	if result == 0: print('Perfect')
	elif result == 1: print('Deficient')
	else: print('Abundant')