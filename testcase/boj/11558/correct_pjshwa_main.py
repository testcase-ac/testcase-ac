import sys

def find_shortest(people_dict, heehyun_num, jookyung_num):
	people_appeared = []
	people_appeared.append(heehyun_num)
	next_num = people_dict[heehyun_num]
	trials = 1
	while(next_num != jookyung_num):
		if next_num in people_appeared:
			return 0
		people_appeared.append(next_num)
		next_num = people_dict[next_num]
		trials += 1
	return trials

testCaseNum = int(sys.stdin.readline())
for i in range(testCaseNum):
	peopleNum = int(sys.stdin.readline())
	people_picked_dict = {}
	for j in range(peopleNum):
		people_picked_dict[j+1] = int(sys.stdin.readline())
	print(find_shortest(people_picked_dict, 1, peopleNum))

