def gcd(a, b):
	while b != 0:
		a, b = b, a % b
	return a

def add_two_rats(r1, r2):
	r1_nom, r1_denom = map(int, r1.split('/'))
	r2_nom, r2_denom = map(int, r2.split('/'))
	new_nom = r1_nom*r2_denom + r2_nom*r1_denom
	new_denom = r1_denom*r2_denom
	return "{}/{}".format(new_nom, new_denom)

def add_multiple_rats(rs):
	result = '0/1'
	for rat in rs:
		result = add_two_rats(result, rat)

	return result

def rat_num(r):
	int_part = 0
	nom, denom = map(int, r.split('/'))
	int_part += (nom // denom)
	nom %= denom

	cd = gcd(nom, denom)
	return (int_part, nom // cd, denom // cd)

def add_rats(rats_list):
	ints = []
	rats = []
	for rat in rats_list:
		if '/' not in rat: ints.append(rat)
		else:
			if ',' in rat:
				sp_rat = rat.split(',')
				ints.append(sp_rat[0])
				rats.append(sp_rat[1])
			else:
				rats.append(rat)
	ints_sum = sum(map(int, ints))
	ints_add, rest_rat_nom, rest_rat_denom = rat_num(add_multiple_rats(rats))
	ints_sum += ints_add
	if ints_sum != 0:
		if rest_rat_nom != 0: return "{},{}/{}".format(ints_sum, rest_rat_nom, rest_rat_denom)
		else: return "{}".format(ints_sum)
	else:
		if rest_rat_nom != 0: return "{}/{}".format(rest_rat_nom, rest_rat_denom)
		else: return "0"

import sys
r = sys.stdin.readline
n = int(r())
idx = 1
while n != 0:
	l = []
	for _ in range(n):
		l.append(r().rstrip())
	print("Test {}: {}".format(idx, add_rats(l)))
	idx += 1
	n = int(r())
