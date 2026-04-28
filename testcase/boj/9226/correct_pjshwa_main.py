import sys
r = sys.stdin.readline

s = r().rstrip()
while(s != '#'):
	for i in range(len(s)):
		if s[i] in 'aeiou':
			print("{}{}{}".format(s[i:], s[:i], "ay"))
			break
	else:
		print("{}{}".format(s, "ay"))
	s = r().rstrip()