n = int(input())
ls = []
for i in range(n):
	a, b, c = input().split()
	b = int(''.join(b.split('.')))
	c = int(''.join(c.split('.')))
	ls.append([a, b, c])

ls.sort(key=lambda a: a[2])

ans = []
ansv = 10**10

for i in range(n):
	fst = ls[i][1]
	other = 0
	names = [ls[i][0]]
	if i <= 2:
		for j in range(4):
			if j == i:
				continue
			other += ls[j][2]
			names.append(ls[j][0])
	else:
		for j in range(3):
			other += ls[j][2]
			names.append(ls[j][0])
	if fst + other < ansv:
		ansv = fst + other
		ans = names

print(ansv / 100)
print('\n'.join(ans))
