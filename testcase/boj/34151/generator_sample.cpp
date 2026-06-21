#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxP = 1000000;
constexpr long long kMaxExp = 1000000000000000000LL;

vector<int> buildPrimes() {
    vector<bool> isPrime(kMaxP + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i <= kMaxP; ++i) {
        if (!isPrime[i]) {
            continue;
        }
        for (int j = i * i; j <= kMaxP; j += i) {
            isPrime[j] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= kMaxP; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

long long randomExp(int mode) {
    if (mode == 0) {
        return rnd.next(1LL, 20LL);
    }
    if (mode == 1) {
        return rnd.next(1LL, 10000LL);
    }
    if (mode == 2) {
        return rnd.next(kMaxExp - 1000000LL, kMaxExp);
    }
    return rnd.next(1LL, kMaxExp);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = buildPrimes();
    vector<vector<long long>> cases;

    const int t = rnd.next(8, 20);
    for (int i = 0; i < t; ++i) {
        const int mode = i % 6;
        int p = primes[rnd.next(static_cast<int>(primes.size()))];
        long long n = 1;
        long long m = 1;

        if (mode == 0) {
            p = primes[rnd.next(0, 30)];
            n = randomExp(0);
            m = n;
        } else if (mode == 1) {
            n = randomExp(0);
            m = randomExp(0);
        } else if (mode == 2) {
            p = rnd.any(vector<int>{2, 3, 5, 999979, 999983});
            n = 1;
            m = randomExp(2);
        } else if (mode == 3) {
            p = rnd.any(vector<int>{2, 3, 5, 999979, 999983});
            n = randomExp(2);
            m = 1;
        } else if (mode == 4) {
            n = randomExp(1);
            m = randomExp(1);
        } else {
            n = randomExp(3);
            m = randomExp(3);
        }

        if (rnd.next(2) == 1) {
            swap(n, m);
        }
        cases.push_back({p, n, m});
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const vector<long long>& testCase : cases) {
        println(testCase[0], testCase[1], testCase[2]);
    }

    return 0;
}
