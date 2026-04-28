import sys, operator

text = sys.stdin.readline().strip().lower()
text_dict = {}
for s in text:
	try:
		text_dict[s] += 1
	except:
		text_dict[s] = 1

sorted_x = sorted(text_dict.items(), key=operator.itemgetter(1),reverse=True)
if sorted_x[0][1] == sorted_x[1][1]:
	print("?")
else:
	print(sorted_x[0][0].upper())