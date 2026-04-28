import sys,string;r=sys.stdin.readline;asciis=string.ascii_uppercase[1:]+'A'
alp_dict={i:j for i,j in zip(string.ascii_uppercase, asciis)}
n=int(r())

for i in range(n):
	print("String #{}".format(i+1))
	print("".join([alp_dict[char] for char in r().rstrip()]))
	print()