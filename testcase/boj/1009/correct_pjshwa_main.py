import sys

testCaseNum = int(sys.stdin.readline())
liasfd = []
for i in range(testCaseNum):
	llist = list(map(int,sys.stdin.readline().split(" ")))
	a = llist[0]; b=llist[1]
	a = a%10
	if (a == 0 or a == 1 or a==5 or a==6):
		if b!=0:
			b = 1
		else:
			b=0
	elif (a == 4 or a == 9):
		if b!=0:
			b = b%2 + 2
		else:
			b=0
		
	else:
		if b!=0:
			b = b%4 + 4
		else:
			b=0
		
	liasfd.append(pow(a,b,10))

for asdkfj in liasfd:
	if asdkfj == 0:
		print(10)
	else:
		print(asdkfj)
