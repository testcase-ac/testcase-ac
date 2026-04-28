x=input().rstrip()

tf = 0
while len(x) != 1:
	x = str(sum(map(int, list(x))))
	tf += 1
print(tf)
if x in '369': print("YES")
else: print("NO")