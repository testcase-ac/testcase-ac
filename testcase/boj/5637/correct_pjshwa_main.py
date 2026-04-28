import sys, re
r = sys.stdin.readlines

word = ''
length = 0
lines = r()
for line in lines:
	line = re.sub('[^-a-zA-Z]+', ' ', line)
	line = line.rstrip().split()
	for j, l in enumerate(map(len, line)):
		if l > length:
			length = l
			word = line[j].lower()

print(word)