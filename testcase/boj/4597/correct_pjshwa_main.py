def parity_decision(string):
	ones = 0
	for char in string:
		if char == '1': ones += 1
	if string[-1] == 'e':
		if ones % 2 == 0: return "{}0".format(string[:-1])
		else: return "{}1".format(string[:-1])
	elif string[-1] == 'o':
		if ones % 2 == 0: return "{}1".format(string[:-1])
		else: return "{}0".format(string[:-1])

import sys;r=sys.stdin.readline
s=r().rstrip()
while s != '#':
	print(parity_decision(s))
	s=r().rstrip()