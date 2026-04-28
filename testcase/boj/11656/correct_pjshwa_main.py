i = input()
l = []
for x in range(len(i)):
    l.append(i[x:])
    
l.sort()
for x in l:
    print(x)