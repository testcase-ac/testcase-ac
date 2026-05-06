import math
n,k=map(int,input().split())
for d in range(-100000,100001):
	t=d*d+4*k*n
	r=math.isqrt(d*d+4*k*n)
	if r*r!=t: continue
	if (-d+r)%(k*2): continue
	p=(-d+r)//(k*2)
	if p<=0: continue
	if n%p: continue
	q=n//p
	if abs(q-k*p)<=100000 and p!=1 and q!=1:
		if p>q: p,q=q,p
		print(f"{p} * {q}")
		break
