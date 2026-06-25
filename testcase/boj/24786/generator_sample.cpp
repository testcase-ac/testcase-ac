#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

vector<int> buildPrimes() {
    vector<int> primes;
    for (int x = 2; x < 1000; ++x) {
        if (isPrime(x)) {
            primes.push_back(x);
        }
    }
    return primes;
}

bool hasValidExponent(int p, int q) {
    int phi = (p - 1) * (q - 1);
    for (int e = 2; e < phi; ++e) {
        if (gcd(e, phi) == 1) {
            return true;
        }
    }
    return false;
}

int chooseE(int phi, int mode) {
    vector<int> candidates;
    for (int e = 2; e < phi; ++e) {
        if (gcd(e, phi) == 1) {
            candidates.push_back(e);
        }
    }

    if (mode == 0) {
        return candidates.front();
    }
    if (mode == 1) {
        return candidates.back();
    }
    if (mode == 2 && candidates.size() >= 4) {
        int limit = min<int>(4, candidates.size());
        return candidates[rnd.next(0, limit - 1)];
    }
    if (mode == 3 && candidates.size() >= 4) {
        int start = max<int>(0, candidates.size() - 4);
        return candidates[rnd.next(start, static_cast<int>(candidates.size()) - 1)];
    }
    return rnd.any(candidates);
}

pair<int, int> choosePrimePair(const vector<int>& primes, int mode) {
    if (mode == 0) {
        int first = rnd.next(0, min<int>(10, primes.size()) - 1);
        int second = rnd.next(0, min<int>(10, primes.size()) - 1);
        while (second == first || !hasValidExponent(primes[first], primes[second])) {
            second = rnd.next(0, min<int>(10, primes.size()) - 1);
        }
        return {primes[first], primes[second]};
    }

    if (mode == 1) {
        int last = static_cast<int>(primes.size()) - 1;
        int first = rnd.next(max(0, last - 10), last);
        int second = rnd.next(max(0, last - 10), last);
        while (second == first || !hasValidExponent(primes[first], primes[second])) {
            second = rnd.next(max(0, last - 10), last);
        }
        return {primes[first], primes[second]};
    }

    if (mode == 2) {
        int first = rnd.next(1, static_cast<int>(primes.size()) - 2);
        int second = first + 1;
        return {primes[first], primes[second]};
    }

    int first = rnd.next(0, static_cast<int>(primes.size()) - 1);
    int second = rnd.next(0, static_cast<int>(primes.size()) - 1);
    while (second == first || !hasValidExponent(primes[first], primes[second])) {
        second = rnd.next(0, static_cast<int>(primes.size()) - 1);
    }
    return {primes[first], primes[second]};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = buildPrimes();
    int t = rnd.next(1, 50);
    println(t);

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int pairMode = rnd.next(0, 4);
        int eMode = rnd.next(0, 4);
        if (caseIndex < 4) {
            pairMode = caseIndex;
            eMode = caseIndex;
        }

        auto [p, q] = choosePrimePair(primes, pairMode);
        int n = p * q;
        int phi = (p - 1) * (q - 1);
        int e = chooseE(phi, eMode);
        println(n, e);
    }

    return 0;
}
