#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

const unsigned long long LIMIT = 1000000000000000000ULL;

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

unsigned long long countProducts(vector<unsigned long long> primes) {
  sort(primes.begin(), primes.end());
  primes.erase(unique(primes.begin(), primes.end()), primes.end());

  set<unsigned long long> products;
  collectProducts(primes, 0, 1, products);
  products.erase(1);
  return products.size();
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  vector<unsigned long long> small = {2,  3,  5,  7,  11, 13, 17, 19,
                                      23, 29, 31, 37, 41, 43, 47};
  vector<unsigned long long> medium = {101, 103, 107, 109, 127, 131, 149,
                                       157, 173, 191, 211, 223, 257};
  vector<unsigned long long> large = {999999937ULL, 1000000007ULL,
                                      1000000009ULL, 2147483647ULL};

  int mode = rnd.next(0, 5);
  vector<unsigned long long> primes;

  if (mode == 0) {
    shuffle(small.begin(), small.end());
    primes = {small[0], small[1], small[2]};
  } else if (mode == 1) {
    unsigned long long p = rnd.any(small);
    primes = {p, p, p};
  } else if (mode == 2) {
    unsigned long long p = rnd.any(small);
    unsigned long long q = rnd.any(medium);
    primes = {p, q, rnd.next(0, 1) == 0 ? p : q};
  } else if (mode == 3) {
    shuffle(medium.begin(), medium.end());
    primes = {medium[0], medium[1], medium[2]};
  } else if (mode == 4) {
    primes = {rnd.any(small), rnd.any(medium), rnd.any(large)};
  } else {
    shuffle(large.begin(), large.end());
    primes = {large[0], large[1], large[2]};
  }

  shuffle(primes.begin(), primes.end());

  unsigned long long count = countProducts(primes);
  unsigned long long i;
  if (count <= 20 || rnd.next(0, 3) == 0) {
    i = rnd.next(1ULL, count);
  } else if (rnd.next(0, 1) == 0) {
    i = rnd.next(1ULL, min(count, 200ULL));
  } else {
    i = rnd.next(max(1ULL, count - min(count, 200ULL) + 1), count);
  }

  cout << primes[0] << ' ' << primes[1] << ' ' << primes[2] << ' ' << i
       << '\n';
  return 0;
}
