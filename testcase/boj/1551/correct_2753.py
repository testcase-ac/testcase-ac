n,k = map(int,input().split())
ls = list(map(int,input().split(',')))
for i in range(k):
	nls = []
	for i in range(len(ls)-1):
		nls.append(ls[i+1]-ls[i])
	ls = nls
print(','.join(str(i) for i in ls))
