able_dict = {
4: ['4'],
7: ['7'],
8: ['4', '4'],
11: ['4', '7'],
12: ['4', '4', '4'],
14: ['7', '7'],
15: ['4', '4', '7'],
16: ['4', '4', '4', '4'],
18: ['4', '7', '7'],
19: ['4', '4', '4', '7'],
20: ['4', '4', '4', '4', '4'],
21: ['7', '7', '7'],
22: ['4', '4', '7', '7'],
23: ['4', '4', '4', '4', '7'],
24: ['4', '4', '4', '4', '4', '4'],
}

import sys, itertools;r=sys.stdin.readline
n=int(r())
if n>24:
	n -= 18
	addition_sevens = n // 7
	n %= 7
	n += 18
	print(" ".join(itertools.chain(able_dict[n], itertools.repeat('7', addition_sevens))))
else:
	if n in able_dict:
		print(" ".join(able_dict[n]))
	else: print('-1')

def biggest_compatible_soo(number):
	# 
