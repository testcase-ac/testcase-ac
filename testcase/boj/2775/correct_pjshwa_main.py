import sys
r = sys.stdin.readline

t = int(r())
apartment_dict = {
	0:[]
}
for i in range(1,15):
	apartment_dict[0].append(i)
	apartment_dict[i] = []
for i in range(1,15):
	apartment_dict[i].append(1)
	for j in range(1,14):
		apartment_dict[i].append(apartment_dict[i][j-1]+apartment_dict[i-1][j])
		
for _ in range(t):
	k = int(r()); n = int(r())
	print(apartment_dict[k][n-1])