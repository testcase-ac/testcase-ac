import sys
r = sys.stdin.readline

class Stack:
	def __init__(self, limit):
		self.stack = []
		self.no = 1
		self.limit = limit
		self.operations = []
	def push(self):
		if self.no <= self.limit:
			self.stack.append(self.no)
			self.no += 1
			self.operations.append("+")
			return True
		else: return False
	def pop(self):
		if self.stack:
			del self.stack[-1]
			self.operations.append("-")
		else: return 0
	def peek(self):
		if self.stack:
			return self.stack[-1]
		else: return 0
	def empty(self):
		if self.stack: return False
		else: return True
	def ops(self):
		for op in self.operations: print(op)

n = int(r())
s = Stack(n)

for _ in range(n):
	doable = True
	next_number = int(r())
	while s.peek() != next_number:
		do = s.push()		
		if not do:
			doable = False
			break
	if not doable: break
	s.pop()

if s.empty(): s.ops()
else: print("NO")