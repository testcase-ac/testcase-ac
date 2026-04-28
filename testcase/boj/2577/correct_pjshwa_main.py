import sys

list_0 = [0] * 10
    
a = int(sys.stdin.readline())
b = int(sys.stdin.readline())
c = int(sys.stdin.readline())
    
product = a * b * c

while(product / 10 != 0):
    digit = product % 10
    product /= 10
    product = int(product)
    list_0[digit] += 1

for i in range(10):
	print(list_0[i])