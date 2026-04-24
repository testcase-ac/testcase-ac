import itertools
import string

N = 20000
print(N)
cnt = 0
# generate distinct words of lengths 50 down to 2 using all 2‐letter combinations (a,b)
# stop as soon as we've printed N words
for a, b in itertools.product(string.ascii_lowercase, repeat=2):
    for L in range(50, 1, -1):
        if cnt >= N:
            break
        # build a word of length L by repeating "ab"
        # if L is odd, append "a" to reach the correct length
        word = (a + b) * (L // 2) + (a if L % 2 else "")
        print(word)
        cnt += 1
    if cnt >= N:
        break
