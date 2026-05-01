# Generate a long alternating-case string to exacerbate use of uninitialized memory in the wrong solution
n = 3000
s = ''.join('A' if i % 2 == 0 else 'a' for i in range(n))
print(s)
