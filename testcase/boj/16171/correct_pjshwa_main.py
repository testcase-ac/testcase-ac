x = input().rstrip()
t = input().rstrip()
s = ""
for c in x:
  if not c.isdigit(): s += c

print(1 if t in s else 0)
