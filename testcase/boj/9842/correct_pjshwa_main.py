from bisect import bisect

def prime_sieve(n):
    """
    Efficient prime sieve, due to Robert William Hanks.
    Source: http://stackoverflow.com/a/2068548
    """
    sieve = [True] * (n//2)
    for i in range(3,int(n**0.5)+1,2):
        if sieve[i//2]:
            sieve[i*i//2::i] = [False] * ((n-i*i-1)//(2*i)+1)
    return [2] + [2*i+1 for i in range(1,n//2) if sieve[i]]

"""
Limit controls the number of primes that are sieved
to cache small values of pi(x).  Without caching,
runtime will be exponential.
When computing pi(x), limit should be
at least sqrt(x).  A higher value of limit
that caches more values can sometimes improve performance.
"""

limit = 10**6
primes = prime_sieve(limit)

phi_cache = {}
def phi(x, a):
    """
    Implementation of the partial sieve function, which
    counts the number of integers <= x with no prime factor less
    than or equal to the ath prime.
    """
    # If value is cached, just return it
    if (x, a) in phi_cache: return phi_cache[(x, a)]

    # Base case: phi(x, a) is the number of odd integers <= x
    if a == 1: return (x + 1) // 2

    result = phi(x, a-1) - phi(x // primes[a-1], a-1)
    phi_cache[(x, a)] = result # Memoize
    return result


pi_cache = {}
def pi(x):
    """
    Computes pi(x), the number of primes <= x, using
    the Meissel-Lehmer algorithm.
    """
    # If value is cached, return it
    if x in pi_cache: return pi_cache[x]

    # If x < limit, calculate pi(x) using a bisection
    # algorithm over the sieved primes.
    if x < limit:
        result = bisect(primes, x)
        pi_cache[x] = result
        return result

    a = pi(int(x ** (1./4)))
    b = pi(int(x ** (1./2)))
    c = pi(int(x ** (1./3)))

    # This quantity must be integral,
    # so we can just use integer division.
    result = phi(x,a) + (b+a-2) * (b-a+1) // 2

    for i in range(a+1, b+1):
        w = x // primes[i-1]
        b_i = pi(w ** (1./2))
        result = result - pi(w)
        if i <= c:
            for j in range(i, b_i+1):
                result = result - pi(w // primes[j-1]) + j - 1
    pi_cache[x] = result
    return result

k = int(input())
left, right = 1, 10**8
while left < right:
  mid = (left + right) // 2
  if pi(mid) < k:
    left = mid + 1
  else:
    right = mid

print(left)
