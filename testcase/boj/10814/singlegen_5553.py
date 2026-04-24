# Generate a maximal test case for the "회원 정렬" problem:
# - N = 100000 (maximum)
# - ages cycle through 1..200 to exercise sorting and stability
# - names are 100 characters long (maximum) and vary with each entry

import sys
N = 100000
print(N)
for i in range(N):
    age = (i % 200) + 1
    # Build a 100-char name by repeating a single letter that cycles A–Z
    ch = chr(ord('A') + (i % 26))
    name = ch * 100
    print(age, name)
