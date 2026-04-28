import sys; r = sys.stdin.readline

n = int(r())

def gcd(a, b):
	while b:
		a, b = b, a % b

	return a

numbers = list(map(int, r().split()))
first_number = numbers[0]

for subsequent_number in numbers[1:]:
	g = gcd(first_number, subsequent_number)
	print("{}/{}".format(first_number // g, subsequent_number // g))