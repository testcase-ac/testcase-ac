# Generate a 50‐character test (25 distinct letters, each twice) 
# which is the maximum allowed length and has all even counts.
s = ''.join(chr(ord('A') + i) * 2 for i in range(25))
print(s)
