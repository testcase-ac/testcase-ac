import sys
r = sys.stdin.readline

def vow(sentence):
	vowels = 0
	for c in sentence.lower():
		if c == 'a' or c == 'e' or c == 'i' or c == 'o' or c == 'u':
			vowels += 1
	return vowels

line = r().rstrip()
while(line != '#'):
	print(vow(line))
	line = r().rstrip()