import sys
r = sys.stdin.readline

s = r().rstrip()
replace_dict = {
	'%': '%25',
	' ': '%20',
	'!': '%21',
	'$': '%24',
	'(': '%28',
	')': '%29',
	'*': '%2a',
}
while s != '#':
	for char in s:
		if char in replace_dict: print(replace_dict[char],end="")
		else: print(char, end="")
	print()
	s = r().rstrip()