s = int(input())
def g(s):
	for i in s:
		yield int(i)
if(s<100): print(s)
else:
    hansu_counter = 99
    for i in range(100,s+1):
        i_s = list(g(str(i)))
        if(i_s[0] - i_s[1] == i_s[1] - i_s[2]): hansu_counter += 1
    print(hansu_counter)
