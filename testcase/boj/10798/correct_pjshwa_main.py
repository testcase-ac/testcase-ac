class ReadVertical:
	def __init__(self, s):
		self.s = s
		self.length = len(s)
		self.index = -1

	def __iter__(self):
		return self

	def __next__(self):
		self.index += 1
		if self.index >= self.length: raise StopIteration
		else: return self.s[self.index]

import sys
r = sys.stdin.readline
strings_list = []
max_len = 0

def update_max_len(length):
	global max_len
	if length > max_len: max_len = length

for _ in range(5):
	s = r().rstrip()
	update_max_len(len(s))
	strings_list.append(ReadVertical(s))

for _ in range(max_len):
	for i in range(5):
		try: print(next(strings_list[i]), end="")
		except StopIteration: pass


