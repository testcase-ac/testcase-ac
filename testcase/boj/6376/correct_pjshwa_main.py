es = [1, 2]
fact = 1

for i in range(2, 10):
	last_e = es[-1]
	fact *= i
	es.append(last_e + 1 / fact)

print('n e')
print('- -----------')

for idx, e_approx in enumerate(es):
	if idx < 3:
		print(f'{idx} {e_approx}')
	else:
		print(f'{idx} {e_approx:.9f}')
