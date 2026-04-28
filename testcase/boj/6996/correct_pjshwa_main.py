n = int(input())

def word_dic(word):
	d = {}
	for l in word:
		if l in d:
			d[l] += 1
		else:
			d[l] = 1
	return d

import sys
for _ in range(n):
	words = sys.stdin.readline().rstrip().split()
	if word_dic(words[0]) == word_dic(words[1]):
		print("{} & {} are anagrams.".format(*words))
	else:
		print("{} & {} are NOT anagrams.".format(*words))
