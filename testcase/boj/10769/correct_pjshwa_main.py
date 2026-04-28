i = input()
a = i.count(r':-)')
b = i.count(r':-(')
if(a==b):
    if(a == 0): print('none')
    else: print('unsure')
elif(a>b): print('happy')
else: print('sad')