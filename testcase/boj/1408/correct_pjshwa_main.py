import sys
start_time = sys.stdin.readline().rstrip('\n').split(':')
end_time = sys.stdin.readline().rstrip('\n').split(':')
h, m, s = map(lambda x, y: int(y)-int(x), start_time, end_time)
if s < 0:
	s += 60
	m -= 1
if m < 0:
	m += 60
	h -= 1
if h < 0: h += 24
print("{0:02d}:{1:02d}:{2:02d}".format(h, m, s))