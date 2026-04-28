n = int(input())

for _ in range(n):
	iterate = 0
	num = input().rstrip()
	while(num != '6174'):
		# print(num)
		num = list(num)
		num = "{:04d}".format(int(''.join(sorted(num, reverse=True))) - int(''.join(sorted(num))))
		iterate += 1
	print(iterate)