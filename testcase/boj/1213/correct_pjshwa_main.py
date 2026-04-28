name = input().rstrip()

name_letter_dict = {}

for char in name:
	if char in name_letter_dict:
		name_letter_dict[char] += 1
	else:
		name_letter_dict[char] = 1

def map_divisible_two(ff):
	def new_func(l):
		new_l = map(lambda x: x % 2 == 0, l)
		return ff(new_l)
	return new_func

@map_divisible_two
def any_false_over_one(l):
	count = 0
	for item in l:
		if not item:
			if count == 0: count += 1
			else: return -1
	if count == 0: return 0
	else: return 1

result = any_false_over_one(name_letter_dict.values())
if result == -1: print("I'm Sorry Hansoo")
else:
	s = sorted(name_letter_dict.keys())
	for item in s:
		for _ in range(name_letter_dict[item] // 2):
			print("{}".format(item), end="")
	if result == 1:
		for item in name_letter_dict:
			if name_letter_dict[item] % 2 != 0:
				print(item, end="")
				break
	s.reverse()
	for item in s:
		for _ in range(name_letter_dict[item] // 2):
			print("{}".format(item), end="")