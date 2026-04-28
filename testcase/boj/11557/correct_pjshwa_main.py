import sys

testCaseNum = int(sys.stdin.readline())
listss = []
for i in range(testCaseNum):
	schoolNum = int(sys.stdin.readline())
	school_key_list = []
	school_value_list = []
	for j in range(schoolNum):
		school_key_value = sys.stdin.readline().split(" ")
		school_key_list.append(school_key_value[0])
		school_value_list.append(int(school_key_value[1]))
	listss.append(school_key_list[school_value_list.index(max(school_value_list))])

for iss in listss:
	print(iss)
