l, m = map(int, input().split())

ans = []
ansp = 10**10

WEEK = 10080

for i in range(m):
	n, p, c, t, r = input().split(',')
	p = int(p)
	c = int(c)
	t = int(t)
	r = int(r)
	
	if WEEK*c*t < l*(r+t):
		continue
	if p < ansp:
		ans = [n]
		ansp = p
	elif p == ansp:
		ans.append(n)


if ans:
	print('\n'.join(ans))
else:
	print('no such mower')
