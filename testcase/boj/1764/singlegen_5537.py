def to_name(i):
    # convert integer i to a unique lowercase string (base-26)
    if i == 0:
        return 'a'
    s = ''
    while i:
        i, r = divmod(i, 26)
        s = chr(ord('a') + r) + s
    return s

N = 500000
M = 500000
print(N, M)
# generate N distinct names
names = [to_name(i) for i in range(N)]
# first list: in numeric order (which is not lex order)
for name in names:
    print(name)
# second list: same names but in reverse order to force sorting in the solution
for name in reversed(names):
    print(name)
