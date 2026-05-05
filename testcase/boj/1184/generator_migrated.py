import random
N = random.randint(1,50);
print(N)
for _ in range(N):
    for _ in range(N):
        K = random.randint(-999,999)
        print(K, end=" ")
    print(" ")
