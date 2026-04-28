code = compile("""

import sys, re
r = sys.stdin.readline

n = int(r())
pattern = '^{}$'.format(re.sub(r'\*', '[a-z]*', r().rstrip()))
for _ in range(n):
	string = r().rstrip()
	if re.match(pattern, string): print("DA")
	else: print("NE")

""", '<string>', 'exec')
exec(code)