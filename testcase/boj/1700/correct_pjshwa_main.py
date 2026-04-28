import sys
r = sys.stdin.readline

n, k = map(int, r().split())
if n >= k:
	print("0")
	sys.exit(0)

electronic_device_dict = {}
items = list(map(int, r().split()))
counts = 0
item_set = set()
while(len(item_set) != n):
	item_set.add(items[counts])
	counts += 1
	if counts >= k:
		print("0")
		sys.exit(0)
sockets = list(item_set)
changed = 0

for i, item in enumerate(items[counts:]):
	if item in electronic_device_dict: electronic_device_dict[item].append(i)
	else: electronic_device_dict[item] = [i]

for item in items:
	if item in electronic_device_dict: electronic_device_dict[item].append(101)
	else: electronic_device_dict[item] = [101]
	 # as inf

def put_item(item):
	global sockets, changed
	for i, it in enumerate(sockets):
		if it == item:
			del electronic_device_dict[item][0]
			return
	most_late = 0
	most_late_index = 0
	for i, it in enumerate(sockets):
		my_next_index = electronic_device_dict[it][0]
		if my_next_index > most_late:
			most_late_index = i
			most_late = my_next_index
	sockets[most_late_index] = item
	del electronic_device_dict[item][0]
	changed += 1
	
for item in items[counts:]:
	put_item(item)

print(changed)
