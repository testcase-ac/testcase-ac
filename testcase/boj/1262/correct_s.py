n,a,b,c,d=map(int,input().split());r=2*n-1
for i in range(a,c+1):print(''.join(chr([46,(e:=abs(i%r+1-n)+abs(j%r+1-n))%26+97][e<n])for j in range(b,d+1)))