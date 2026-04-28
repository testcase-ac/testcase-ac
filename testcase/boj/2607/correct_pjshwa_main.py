import sys

n = int(input())
ex_word = sys.stdin.readline().rstrip()
l = len(ex_word)
ex_dic = {}
for w in ex_word:
	if w in ex_dic.keys():
		ex_dic[w] += 1
	else:
		ex_dic[w] = 1

value_sum = sum(ex_dic.values())
similar_words_count = 0

for i in range(n - 1):
	comp_word = sys.stdin.readline().rstrip()
	w_l = len(comp_word)
	comp_dic = {}
	for w in comp_word:
		if w in comp_dic.keys():
			comp_dic[w] += 1
		else:
			comp_dic[w] = 1

	me_similar = True
	comp_value_sum = 0
	if w_l + 1 == l:
		violate = 0
		for w in ex_dic.keys():
			if w not in comp_dic.keys(): comp_dic[w] = 0
			else: comp_value_sum += comp_dic[w]
			if ex_dic[w] != comp_dic[w]:
				if ex_dic[w] != comp_dic[w] + 1:
					me_similar = False
					break
				else:
					violate += 1
			if violate > 1:
				me_similar = False
				break
		if comp_value_sum + 1 != value_sum: me_similar = False
	elif w_l == l + 1:
		violate = 0
		for w in ex_dic.keys():
			if w not in comp_dic.keys():
				me_similar = False
				break
			else: comp_value_sum += comp_dic[w]
			if ex_dic[w] != comp_dic[w]:
				if ex_dic[w] != comp_dic[w] - 1:
					me_similar = False
					break
				else:
					violate += 1
			if violate > 1:
				me_similar = False
				break
		if comp_value_sum < value_sum: me_similar = False
	elif w_l == l:
		violate = 0
		for w in ex_dic.keys():
			if w not in comp_dic.keys(): comp_dic[w] = 0
			else: comp_value_sum += comp_dic[w]
			if ex_dic[w] != comp_dic[w]:
				if ex_dic[w] != comp_dic[w] - 1 and ex_dic[w] != comp_dic[w] + 1:
					me_similar = False
					break
				else:
					violate += 1
			if violate > 1:
				me_similar = False
				break
		if comp_value_sum +1 < value_sum: me_similar = False
	else:
		me_similar = False
	if me_similar: similar_words_count += 1
print(similar_words_count)