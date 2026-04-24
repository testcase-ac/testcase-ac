k=[1,1,2,4]
while(len(k)<68):
    k.append(sum(k[-4:]))
exec('print(k[int(input())]);'*int(input()))
