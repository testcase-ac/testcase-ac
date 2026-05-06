while True:
    try:
        n=int(input())
        k=0
        for i in range(2,n+1):
            if i%2==1: k=k*2-1
            else: k=k*2+1
        print(k)
    except:
        break
