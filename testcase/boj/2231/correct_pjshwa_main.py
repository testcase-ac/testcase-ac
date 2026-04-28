def split_sum(number):
	return number + sum(map(int, list(str(number))))

n = int(input())
j = n-54
if j<1:j=1
for i in range(j, n+1):
	if split_sum(i) == n:
		print(i);break
else:
	print(0)