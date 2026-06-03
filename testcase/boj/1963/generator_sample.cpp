#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static bool isPrime(int n) {
    if (n < 2) {
        return false;
    }
    for (int d = 2; d * d <= n; ++d) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

static int changedDigits(int a, int b) {
    string x = to_string(a);
    string y = to_string(b);
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (x[i] != y[i]) {
            ++count;
        }
    }
    return count;
}

static bool hasInternalZero(int n) {
    string s = to_string(n);
    return s[1] == '0' || s[2] == '0' || s[3] == '0';
}

static int pickPrimeWithInternalZero(const vector<int>& primes) {
    vector<int> candidates;
    for (int p : primes) {
        if (hasInternalZero(p)) {
            candidates.push_back(p);
        }
    }
    return rnd.any(candidates);
}

static int pickOneDigitNeighbor(int a, const vector<int>& primes) {
    vector<int> neighbors;
    for (int b : primes) {
        if (changedDigits(a, b) == 1) {
            neighbors.push_back(b);
        }
    }
    return rnd.any(neighbors);
}

static int pickFromRange(const vector<int>& primes, int lo, int hi) {
    vector<int> candidates;
    for (int p : primes) {
        if (lo <= p && p <= hi) {
            candidates.push_back(p);
        }
    }
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes;
    for (int n = 1000; n <= 9999; ++n) {
        if (isPrime(n)) {
            primes.push_back(n);
        }
    }

    int t = rnd.next(8, 30);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 5);
        int a = rnd.any(primes);
        int b = rnd.any(primes);

        if (mode == 0) {
            b = a;
        } else if (mode == 1) {
            b = pickOneDigitNeighbor(a, primes);
        } else if (mode == 2) {
            a = pickPrimeWithInternalZero(primes);
            b = rnd.next(0, 1) ? pickOneDigitNeighbor(a, primes) : rnd.any(primes);
        } else if (mode == 3) {
            a = pickFromRange(primes, 1000, 1999);
            b = pickFromRange(primes, 8000, 9999);
        } else if (mode == 4) {
            a = pickFromRange(primes, 9000, 9999);
            b = pickFromRange(primes, 1000, 2999);
        }

        cases.push_back({a, b});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const auto& testCase : cases) {
        println(testCase.first, testCase.second);
    }

    return 0;
}
