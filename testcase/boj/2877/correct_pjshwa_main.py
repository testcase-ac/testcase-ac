i=1;n=int(input())
while (2**i)-2<n:i+=1
i-=1;n-=((2**i)-2);fs='{:0%db}'%i;fs=fs.format(n-1);fs=fs.replace('0','4');print(fs.replace('1','7'))