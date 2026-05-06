import random
def generate_random_large_numbers():
    m_len = random.randint(1, 499)
    is_negative_m = random.choice([True, False])
    is_negative_n = random.choice([True, False])
    m = str(random.randint(1, 9)) + ''.join(random.choices('0123456789', k=m_len - 1))
    n = str(random.randint(1, 9)) + ''.join(random.choices('0123456789', k=m_len - 1))
    if is_negative_m:
        m = '-' + m
    if is_negative_n:
        n = '-' + n
    return m, n
m, n = generate_random_large_numbers()
print(f"{m} {n}")
