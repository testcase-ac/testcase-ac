import sys
r=sys.stdin.readline

def vowel_tester(string):
	for v in 'aeiou':
		if v in string: return True
	return False

def three_streak_tester(string):
	s = string.lower()
	vowel = False
	if s[0] in 'aeiou': vowel = True
	streak = 0
	for char in s:
		if char in 'aeiou':
			if vowel: streak += 1
			else:
				vowel = True
				streak = 1
		else:
			if vowel:
				vowel = False
				streak = 1
			else: streak += 1
		if streak >= 3: return False
	return True

def same_char_tester(string):
	s = string.lower()
	c_char = s[0]
	for char in s[1:]:
		if char == c_char and char not in 'eo': return False
		else: c_char = char
	return True

s = r().rstrip()
while s != 'end':
	if vowel_tester(s) and three_streak_tester(s) and same_char_tester(s):
		print("<{}> is acceptable.".format(s))
	else:
		print("<{}> is not acceptable.".format(s))
	s = r().rstrip()