#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> buildPrimes() {
    const int maxP = 3000000;
    vector<bool> isPrime(maxP + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= maxP; ++i) {
        if (!isPrime[i]) {
            continue;
        }
        for (int j = i * i; j <= maxP; j += i) {
            isPrime[j] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= maxP; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

long long chooseK(int mode) {
    if (mode == 0) {
        return rnd.next(1LL, 200LL);
    }
    if (mode == 1) {
        return rnd.next(1LL, 1000000LL);
    }
    if (mode == 2) {
        return rnd.next(999999000000LL, 1000000000000LL);
    }
    if (mode == 3) {
        return rnd.any(vector<long long>{1LL, 2LL, 3LL, 999999937LL, 1000000000000LL});
    }
    return rnd.next(1LL, 1000000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = buildPrimes();
    const int primeCount = int(primes.size());

    int mode = rnd.next(5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(1, 12);
    } else if (mode == 3) {
        n = rnd.next(1, 30);
    } else {
        n = rnd.next(30, 80);
    }

    vector<int> candidates;
    if (mode == 0) {
        for (int i = 0; i < min(primeCount, 40); ++i) {
            candidates.push_back(primes[i]);
        }
    } else if (mode == 1) {
        int start = rnd.next(0, 500);
        for (int i = start; i < min(primeCount, start + 200); ++i) {
            candidates.push_back(primes[i]);
        }
    } else if (mode == 2) {
        for (int i = max(0, primeCount - 300); i < primeCount; ++i) {
            candidates.push_back(primes[i]);
        }
    } else if (mode == 3) {
        for (int i = 0; i < 20; ++i) {
            candidates.push_back(primes[i]);
        }
        for (int i = max(0, primeCount - 80); i < primeCount; ++i) {
            candidates.push_back(primes[i]);
        }
    } else {
        candidates = primes;
    }

    shuffle(candidates.begin(), candidates.end());
    vector<int> selected(candidates.begin(), candidates.begin() + n);
    shuffle(selected.begin(), selected.end());

    println(n);
    println(selected);
    println(chooseK(mode));
    return 0;
}
