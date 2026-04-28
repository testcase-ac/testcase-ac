block_dict = {'1':['4','5'],
'2':[],
'3':['4','5'],
'4':['2','3'],
'5':['8'],
'6':['2','3'],
'7':['8'],
'8':['6','7'],
}

import sys
s = sys.stdin.readline().rstrip()
index = 1
while(s != '0'):
	l = len(s)
	is_valid = True
	if s[0] != '1' or s[l-1] != '2':
		is_valid = False
	for i in range(l-1):
		if s[i+1] not in block_dict[s[i]]:
			is_valid = False
			break
	if is_valid:
		print("{}. VALID".format(index))
	else:
		print("{}. NOT".format(index))

	index += 1
	s = sys.stdin.readline().rstrip()