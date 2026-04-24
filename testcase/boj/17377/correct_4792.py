import sys
def debug(s):
	#print(s)
	pass
a, b, c = map(int, input().split())
n = int(input())
pos = {}
oil = {}
nxt = 0
for _ in range(n):
	s = input().split()
	p = int(s[-2]), int(s[-1])
	name = ' '.join(i for i in s[:-2])
	pos[name] = p
	debug(f'{name} is at pos {p}')

for i in range(3):
	s = input().split()
	name = ' '.join(i for i in s[:-1])
	oil[name] = int(s[-1])/c  # oil[name]: how much for 1 dist?
	debug(f'oil station {name} has cost {oil[name]}')

curdist = a*c
money = 0
passenger = {}  # pos -> list of cur costs
curpos = 'Taxi Garage'
def distance(a, b):
	return abs(a[0]-b[0])+abs(a[1]-b[1])
passcnt = 0
debug(f'current passenger: {passenger}')
debug(f'curdist={curdist}, money={money}, curpos={curpos}')
k = int(input())
for line in sys.stdin:
	inp = line.strip()
	debug(f'\nCommand: {inp}')
	goto = inp[0] == 'G'
	if goto:
		name = ' '.join(i for i in inp.split()[2:])[:-1]
	else:
		name = ' '.join(i for i in inp.split()[5:])[:-1]

	if goto:
		dist = distance(pos[curpos], pos[name])
		debug(f'distance between {curpos}({pos[curpos]}) and {name}({pos[name]}) is {dist}')
		curdist -= dist
		if curdist < 0:
			print('OUT OF GAS')
			exit(0)
		for k in passenger:
			for i in range(len(passenger[k])):
				passenger[k][i] += dist*b
		if name in passenger and passenger[name]:
			for i in passenger[name]:
				debug(f'i={i}, money={money}')
				money += i
			passcnt -= len(passenger[name])
			passenger[name] = []
		if name in oil:
			needdist = a*c-curdist
			needmoney = int(needdist*oil[name])
			if needmoney <= money:
				curdist = a*c
				money -= needmoney
			else:
				curdist += money / oil[name]
				money = 0
		curpos = name

	else:
		if passcnt == 3:
			print('CAPACITY FULL')
			exit(0)
		if name not in passenger:
			passenger[name] = []
		passenger[name].append(0)
		passcnt += 1
	debug(f'current passenger: {passenger}')
	debug(f'curdist={curdist}, money={money}, curpos={curpos}, passcnt={passcnt}')

if curpos != 'Taxi Garage':
	print('NOT IN GARAGE')
elif passcnt:
	print('REMAINING PASSENGER')
else:
	print(money)
