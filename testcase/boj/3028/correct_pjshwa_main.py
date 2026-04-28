balls = {
	1:1,
	2:0,
	3:0
}
import sys
for op in sys.stdin.readline().rstrip():
	if op == 'A':
		balls[1], balls[2] = balls[2], balls[1]
	elif op == 'B':
		balls[2], balls[3] = balls[3], balls[2]
	elif op == 'C':
		balls[1], balls[3] = balls[3], balls[1]
for item in balls:
	if balls[item] == 1:
		print(item)
		break