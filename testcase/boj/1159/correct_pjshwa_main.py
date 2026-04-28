n = int(input())

surname_dict = {}
for _ in range(n):
	surname = input()[0]
	if surname in surname_dict:
		surname_dict[surname] += 1
	else:
		surname_dict[surname] = 1
		
l = [s for s, v in surname_dict.items() if v >= 5]
if not l: 
	print("PREDAJA")
else:
	for item in sorted(l):
		print(item, end="")