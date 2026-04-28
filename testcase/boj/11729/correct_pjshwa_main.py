class Stack:
	def __init__(self):
		self.stack = []

	def push(self, no):
		self.stack.insert(0, no)

	def pop(self):
		if self.stack:
			t = self.stack[0]
			del self.stack[0]
			return t

	def top(self):
		if self.stack:
			return self.stack[0]

	def __str__(self):
		print(self.stack)

towers = [Stack()] * 3
n = int(input())
for i in range(1,n+1):
	towers[0].push(i)

movements = []
def hanoi(fro, to, num_of_towers):
	global movements
	temp_base = 0
	# print(towers)
	for i in range(3):
		if i != fro and i != to:
			temp_base=i;break
	if num_of_towers == 1:
		towers[to].push(towers[fro].pop())
		movements.append((fro+1, to+1))
	else:
		hanoi(fro, temp_base, num_of_towers-1)
		towers[to].push(towers[fro].pop())
		movements.append((fro+1, to+1))
		hanoi(temp_base, to, num_of_towers-1)
hanoi(0,2,n)
print(len(movements))
for move in movements:
	print("{} {}".format(*move))