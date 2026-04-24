def stoi(s):
	s = list(map(int,s.split(':')))
	return s[0] * 3600 + s[1] * 60 + s[2]
def itos(i):
	return '%02d:%02d:%02d' % (i // 3600, (i%3600)//60, i%60)
a,b = stoi(input()), stoi(input())
if b <= a:
	b += 86400
print(itos(b-a))


