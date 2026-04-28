import sys
r = sys.stdin.readline

string_1 = r().rstrip()
string_2 = r().rstrip()

def dict_by_count(string):
	new_dict = {}
	for char in string:
		if char in new_dict:
			new_dict[char] += 1
		else:
			new_dict[char] = 1

	return new_dict

dict_1 = dict_by_count(string_1)
dict_2 = dict_by_count(string_2)

missing_char_count = 0

for key in dict_1:
	if key not in dict_2:
		missing_char_count += dict_1[key]
	elif dict_2[key] > dict_1[key]:
		missing_char_count += (dict_2[key] - dict_1[key])

for key in dict_2:
	if key not in dict_1:
		missing_char_count += dict_2[key]
	elif dict_1[key] > dict_2[key]:
		missing_char_count += (dict_1[key] - dict_2[key])

print(missing_char_count)