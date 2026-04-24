n = int(input())
for i in range(n):
    t = int(input())
    if t == 1:
        print('#\n')
    elif t == 2:
        print('##\n##\n')
    else:
        print('#'*t)
        for i in range(t-2):
            print('#'+'J'*(t-2)+'#')
        print('#'*t+'\n')
        
