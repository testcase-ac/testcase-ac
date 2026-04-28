md = {}
def second(ass):
	ass = list(ass);i = 0;l = len(ass)
	while i < l-1:
		if md[ass[i]] > md[ass[i+1]]:ass[i], ass[i+1] = ass[i+1], ass[i];i+=1
		i += 1
	return ''.join(ass)
import sys;r=sys.stdin.readline;n1,n2=map(int,r().split());ag_1 = r().rstrip()
for ant in ag_1:md[ant] = 1
ag_2 = r().rstrip()
for ant in ag_2:md[ant] = -1
s = "{}{}".format(ag_1[::-1], ag_2);ss = int(r())
for _ in range(ss):s = second(s)
print(s)