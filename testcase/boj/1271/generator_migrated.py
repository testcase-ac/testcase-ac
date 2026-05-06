import random
def generate_random_large_numbers():
    m_len = random.randint(1, 499)
    n_len = random.randint(m_len, 499)
    m = random.choice('123456789') + ''.join(random.choices('0123456789', k=m_len-1))
    n = random.choice('123456789') + ''.join(random.choices('0123456789', k=n_len-1))
    return m, n
m, n = generate_random_large_numbers()
if len(m)<len(n):
  t=m
  m=n
  n=t
print(f"{m} {n}")
