catalan_list = [1,1,2,5,14]

n = int(input())

def add_catalan_list(index):
	new_number = 0
	for i in range(index // 2):
		new_number += 2 * (catalan_list[0+i] * catalan_list[index-1-i])
	if index % 2 == 1:
		new_number += (catalan_list[index // 2] ** 2)
	return new_number

for i in range(5,31):
	catalan_list.append(add_catalan_list(i))

while(n != 0):
	print(catalan_list[n])
	n = int(input())