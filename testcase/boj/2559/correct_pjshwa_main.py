import sys; r = sys.stdin.readline

n, k = map(int, r().split())

sequence = list(map(int, r().split()))

running_sum = sum(sequence[0:k])
max_sum = running_sum

for i in range(n-k):
	running_sum += sequence[i+k]
	running_sum -= sequence[i]
	if running_sum > max_sum: max_sum = running_sum

print(max_sum)