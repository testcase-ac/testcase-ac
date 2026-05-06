import sys
import random
if len(sys.argv) > 1:
    random.seed(int(sys.argv[1]))
# GPT 코드
import random

def is_prime(n):
    if n < 2:
        return False
    small = [2,3,5,7,11,13,17,19,23,29]
    for p in small:
        if n % p == 0:
            return n == p

    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1

    # 64~128비트 이상도 안전하게 쓰는 베이스들
    for a in [2,325,9375,28178,450775,9780504,1795265022]:
        if a % n == 0:
            continue
        x = pow(a, d, n)
        if x == 1 or x == n-1:
            continue
        for _ in range(s-1):
            x = pow(x, 2, n)
            if x == n-1:
                break
        else:
            return False
    return True

while True:
    # 약 60비트 소수 → n은 최대 120비트 수준
    p = random.getrandbits(60)
    if not is_prime(p):
        continue

    k = random.randint(2, 10**8)
    d = random.randint(-100000, 100000)

    q = k*p + d
    if q < p:
        continue
    if not is_prime(q):
        continue

    n = p*q
    if 1 < n < 10**120:
        print(n, k)
        break
