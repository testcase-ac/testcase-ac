def digit_sum(number, base):
	digits = []
	while number != 0:
		digits.append(number % base)
		number //= base
	return sum(digits)

for i in range(1000,10000):
	digit_10 = digit_sum(i,10)
	digit_12 = digit_sum(i,12)
	digit_16 = digit_sum(i,16)
	if digit_10 == digit_12 and digit_12 == digit_16:
		print(i)
