#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const unsigned long long LIMIT = 1000000000000000000ULL;

unsigned long long mulMod(unsigned long long a, unsigned long long b,
                          unsigned long long mod) {
  return static_cast<unsigned long long>((__uint128_t)a * b % mod);
}

unsigned long long powMod(unsigned long long a, unsigned long long e,
                          unsigned long long mod) {
  unsigned long long result = 1;
  while (e > 0) {
    if (e & 1) result = mulMod(result, a, mod);
    a = mulMod(a, a, mod);
    e >>= 1;
  }
  return result;
}

bool isPrime(unsigned long long n) {
  if (n < 2) return false;
  for (unsigned long long p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL,
                              19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
    if (n == p) return true;
    if (n % p == 0) return false;
  }

  unsigned long long d = n - 1;
  int s = 0;
  while ((d & 1) == 0) {
    d >>= 1;
    ++s;
  }

  for (unsigned long long a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL,
                              19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
    if (a >= n) continue;
    unsigned long long x = powMod(a, d, n);
    if (x == 1 || x == n - 1) continue;

    bool composite = true;
    for (int r = 1; r < s; ++r) {
      x = mulMod(x, x, n);
      if (x == n - 1) {
        composite = false;
        break;
      }
    }
    if (composite) return false;
  }
  return true;
}

void collectProducts(const vector<unsigned long long>& primes, int index,
                     unsigned long long current,
                     set<unsigned long long>& products) {
  if (index == static_cast<int>(primes.size())) {
    products.insert(current);
    return;
  }

  unsigned long long value = current;
  while (value < LIMIT) {
    collectProducts(primes, index + 1, value, products);
    if (value > (LIMIT - 1) / primes[index]) break;
    value *= primes[index];
  }
}

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  long long p1 = inf.readLong(2LL, 999999999999999999LL, "p_1");
  inf.readSpace();
  long long p2 = inf.readLong(2LL, 999999999999999999LL, "p_2");
  inf.readSpace();
  long long p3 = inf.readLong(2LL, 999999999999999999LL, "p_3");
  inf.readSpace();
  long long i = inf.readLong(1LL, 999999999999999999LL, "i");
  inf.readEoln();
  inf.readEof();

  vector<unsigned long long> primes = {static_cast<unsigned long long>(p1),
                                       static_cast<unsigned long long>(p2),
                                       static_cast<unsigned long long>(p3)};
  for (int idx = 0; idx < 3; ++idx) {
    ensuref(isPrime(primes[idx]), "p_%d is not prime: %llu", idx + 1,
            primes[idx]);
  }

  sort(primes.begin(), primes.end());
  primes.erase(unique(primes.begin(), primes.end()), primes.end());
  // CHECK: the statement says three prime numbers, but does not require them
  // to be distinct; equal primes define the same allowed prime-factor set.
  set<unsigned long long> products;
  collectProducts(primes, 0, 1, products);
  products.erase(1);

  ensuref(static_cast<unsigned long long>(i) <= products.size(),
          "H_i is not guaranteed to be less than 10^18: i=%lld, count=%zu", i,
          products.size());
}
