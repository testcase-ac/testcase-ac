n = int(input())
ls = input().split()


for i, item in enumerate(ls):
	if item == 'mumble':
		continue
	item = int(item)
	if item != i+1:
		print('something is fishy')
		exit(0)
print('makes sense')
