import random, string

# Maximum constraints
N = 100_000
M = 1

print(N, M)
random.seed(0)
words = set()
# generate N distinct words of length 1 to 10
while len(words) < N:
    L = random.randint(1, 10)
    w = ''.join(random.choices(string.ascii_lowercase, k=L))
    words.add(w)

# output them in arbitrary order
for w in words:
    print(w)
