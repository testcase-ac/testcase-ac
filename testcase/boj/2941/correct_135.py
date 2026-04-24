s = input()
for r in ['c=', "c-", "dz=", "d-", "lj", "nj", "s=", "z="]:
    s = s.replace(r, 'x')
print(len(s))
