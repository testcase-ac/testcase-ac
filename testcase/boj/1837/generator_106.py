import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

K_MIN = 2

# Adjust K_MAX to be small (e.g., 100) with a 50% chance
if random.choice([True, False]):
    K_MAX = 100
else:
    K_MAX = 1_000_000

PQ_MIN = 2

# Adjust PQ_MAX to be small (e.g., 10,000) with a 50% chance
if random.choice([True, False]):
    PQ_MAX = 100
else:
    PQ_MAX = 1_000_000

def sieve_primes_upto(n):
    sieve = [True] * (n+1)
    sieve[0] = sieve[1] = False
    for i in range(2, int(n ** 0.5)+1):
        if sieve[i]:
            for multiple in range(i*i, n+1, i):
                sieve[multiple] = False
    primes = [i for i, is_prime in enumerate(sieve) if is_prime]
    return primes

# Generate primes up to the maximum required value
max_prime_needed = max(K_MAX + 100, PQ_MAX)
primes_list = sieve_primes_upto(max_prime_needed)

def random_prime_between(a, b):
    primes_in_range = [p for p in primes_list if a <= p <= b]
    if not primes_in_range:
        return None
    return random.choice(primes_in_range)

def is_prime(n):
    if n < 2:
        return False
    for p in primes_list:
        if p * p > n:
            break
        if n % p == 0:
            return n == p
    d = primes_list[-1] + 1
    while d * d <= n:
        if n % d == 0:
            return False
        d += 1
    return True

def next_prime_at_least(n):
    candidate = max(2, n)
    while not is_prime(candidate):
        candidate += 1
    return candidate

def prime_between_or_after(a, b):
    prime = random_prime_between(a, b)
    if prime is not None:
        return prime
    return next_prime_at_least(a)

def generate_good_key():
    K = random.randint(K_MIN, K_MAX)
    p = prime_between_or_after(K, PQ_MAX)
    q = prime_between_or_after(K, PQ_MAX)
    P = p * q
    return P, K

def generate_bad_key():
    K = random.randint(K_MIN, K_MAX)
    p = random_prime_between(PQ_MIN, K - 1)
    if p is None:
        p = 2
    q = prime_between_or_after(K, PQ_MAX)
    P = p * q
    return P, K

def generate_testcase_triggering_bug():
    # Select a prime K within the specified range
    possible_K = [p for p in primes_list if K_MIN <= p <= K_MAX]
    if not possible_K:
        # If no primes in range, pick a random K
        K = random.randint(K_MIN, K_MAX)
    else:
        K = random.choice(possible_K)
    
    # Select a prime q greater than K but within PQ_MAX
    q = prime_between_or_after(K + 1, PQ_MAX)
    
    P = K * q  # Compute P as the product of K and a larger prime q
    return P, K

def generate_testcase():
    # Randomly choose between the two methods
    if random.choice([True, False]):
        # Use the original generator (good or bad key)
        if random.choice([True, False]):
            P, K = generate_good_key()
        else:
            P, K = generate_bad_key()
    else:
        # Use the generator that triggers the bug
        P, K = generate_testcase_triggering_bug()
    
    print(f"{P} {K}")

generate_testcase()
