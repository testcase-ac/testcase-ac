n = int(input())
import sys
files = map(int, sys.stdin.readline().split())
cluster = int(input())
def real(file):
	if file % cluster == 0:
		return file
	else:
		return (file // cluster + 1) * cluster
print(sum(map(real, files)))