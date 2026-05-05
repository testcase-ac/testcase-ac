import random

# 최대 어디까지 틀리는지 확인하는 코드
def sub_str_int(s, n):
    s = list(s)
    i = len(s) - 1
    while n > 0 and i >= 0:
        d = int(s[i]) - (n % 10)
        n //= 10
        if d < 0:
            d += 10
            n += 1
        s[i] = chr(d + 48)
        i -= 1
    while i >= 0 and n > 0:
        d = int(s[i]) - 1
        if d < 0:
            s[i] = '9'
            i -= 1
        else:
            s[i] = chr(d + 48)
            break
    result = ''.join(s).lstrip('0')
    return result if result else '0'

N = random.randint(1, 10**5)
A = '9' * (10**6)

A2 = sub_str_int(A, N)
print(A2, A2)
