import sys
n, m = map(int, sys.stdin.readline().split())

n_m_power_list = [0,0]
n_power_list = [0,0]
m_power_list = [0,0]

def fill_power_list(n_list, up_to):
	two_power = 2
	five_power = 5

	while(up_to >= two_power):
		n_list[0] += (up_to // two_power)
		two_power *= 2
	while(up_to >= five_power):
		n_list[1] += (up_to // five_power)
		five_power *= 5

fill_power_list(n_power_list, n)
fill_power_list(m_power_list, m)
fill_power_list(n_m_power_list, n-m)

print(min(n_power_list[0]-(m_power_list[0]+n_m_power_list[0]),n_power_list[1]-(m_power_list[1]+n_m_power_list[1])))