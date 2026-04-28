n = int(input())

serials = []
import sys, re

def word_digit_sum(string):
	return sum(map(int, re.findall('[0-9]', string)))

for _ in range(n):
	string = sys.stdin.readline().rstrip()
	serials.append((string, word_digit_sum(string)))

serials.sort(key = lambda x: (len(x[0]), x[1], x[0]))

for s in serials:
	print(s[0])
