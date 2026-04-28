def hanoi(fr, to, size):
	if size == 1:
		print("{} {}".format(fr, to))
	else:
		hanoi(fr, 6-fr-to, size-1)
		print("{} {}".format(fr, to))
		hanoi(6-fr-to, to, size-1)

def hanoi_k_wrapper(fr, to, size):
	print((2**size) - 1)
	if size <= 20:
		hanoi(fr, to, size)

hanoi_k_wrapper(1, 3, int(input()))