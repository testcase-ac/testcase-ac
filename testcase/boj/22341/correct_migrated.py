def f(a,b,x,y):
    if a<=x or b<=y:return a,b
    if x*b<a*y:return a,y
    else:return x,b
n,c=map(int,input().split())
a=b=n
for _ in range(c):
  x,y=map(int,input().split())
  a,b=f(a,b,x,y)
print(a*b)
