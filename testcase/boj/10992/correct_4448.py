print((lambda n,e,s: '\n'.join(e*(n-1)+s if i==0 else s*(2*n-1) if i==n-1 else e*(n-1-i)+s+e*(2*i-1)+s for i in range(n)))(int(input()),' ','*'))
