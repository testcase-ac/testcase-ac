idx=0
res=0
for char in '{:b}'.format(int(input()))[::-1]:
    res += (3**idx)*int(char)
    idx+=1
print(res)