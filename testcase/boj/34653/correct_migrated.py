import sys
from bisect import bisect_left
from fractions import Fraction
from math import atan2
def ccw(A,B,C):
    v1=B[0]-A[0],B[1]-A[1]
    v2=C[0]-A[0],C[1]-A[1]
    if v1[0]*v2[1]-v1[1]*v2[0]>0:return 1
    elif v1[0]*v2[1]-v1[1]*v2[0]<0:return -1
    else:return 0
def dist(A,B): return (A[0]-B[0])**2+(A[1]-B[1])**2
input=sys.stdin.readline
n=int(input())
l=[]
for i in range(n):
    l.append(list(map(int,input().split())))
    if i==0:l.append([l[-1][0],2*10**9])
    if i==n-1:l.append([l[-1][0],2*10**9])
p=min(l,key=lambda t: (t[1],t[0]))
l.remove(p)
l.sort(key=lambda t: (atan2(t[1]-p[1],t[0]-p[0]),dist(t,p)))
# print(l)
# for t in l:print(atan2(t[1]-p[1],t[0]-p[0]))
s=[p,l[0]]
for i in range(1,n+1):
    j=l[i]
    s.append(j)
    while len(s)>=3:
        c=ccw(s[-3],s[-2],s[-1])
        if c<=0:s.pop(-2)
        else:break
while len(s)>=3:
    c=ccw(s[-2],s[-1],s[0])
    if c<=0:s.pop(-2)
    else:break
s=[i for i in s if i[1]<2*10**9]
s.sort() #[[1, 4], [4, 3], [11, 2]]
q=int(input())
for i in range(q):
    d=int(input())
    idx=bisect_left(s,d,key=lambda t:t[0])
    L,R=s[idx-1],s[idx]
    sl=Fraction(R[1]-L[1],R[0]-L[0])
    ans=L[1]+sl*(d-L[0])
    print(ans.numerator,ans.denominator)
