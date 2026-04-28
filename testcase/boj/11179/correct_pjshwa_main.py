def reverse_binary(number):
	b_list = []
	while number != 0:
		b_list.append(number % 2)
		number //= 2
	l = len(b_list)
	result = 0
	for i in range(l):
		result += (2 ** (l - i - 1) * b_list[i])
	return result

print(reverse_binary(int(input())))