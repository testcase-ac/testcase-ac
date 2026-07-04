#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using Bank = pair<long long, long long>;

long long randomNearLimit() {
    return rnd.next(1000000000LL - 200000LL, 1000000000LL);
}

Bank coprimePair(long long lo, long long hi) {
    long long x;
    long long y;
    do {
        x = rnd.next(lo, hi);
        y = rnd.next(lo, hi);
    } while (gcd(x, y) != 1);
    return {x, y};
}

Bank nonCoprimePair(long long lo, long long hi) {
    long long factor = rnd.next(2LL, 100LL);
    long long maxBase = hi / factor;
    long long minBase = max(1LL, (lo + factor - 1) / factor);
    if (minBase > maxBase) {
        minBase = 1;
    }
    long long a = rnd.next(minBase, maxBase);
    long long b = rnd.next(minBase, maxBase);
    return {a * factor, b * factor};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 4) {
        n = rnd.next(40, 80);
    } else if (mode == 5) {
        n = rnd.next(20, 45);
    } else {
        n = rnd.next(8, 30);
    }

    vector<Bank> banks;
    banks.reserve(n);

    banks.push_back({1, rnd.next(1LL, 30LL)});
    banks.push_back({rnd.next(1LL, 30LL), 1});
    banks.push_back({rnd.next(2LL, 50LL), rnd.next(2LL, 50LL)});
    banks.push_back({rnd.next(2LL, 40LL) * 2, rnd.next(2LL, 40LL) * 2});
    banks.push_back(coprimePair(2, 100));
    banks.push_back(nonCoprimePair(2, 1000));

    if (mode == 0) {
        while ((int)banks.size() < n) {
            banks.push_back(coprimePair(2, 200));
        }
    } else if (mode == 1) {
        while ((int)banks.size() < n) {
            banks.push_back(nonCoprimePair(2, 5000));
        }
    } else if (mode == 2) {
        while ((int)banks.size() < n) {
            long long x = rnd.next(1LL, 200LL);
            long long y = x + rnd.next(-5LL, 5LL);
            y = max(1LL, min(1000000000LL, y));
            banks.push_back({x, y});
        }
    } else if (mode == 3) {
        while ((int)banks.size() < n) {
            long long x = rnd.next(1LL, 1000LL);
            long long y = rnd.next(1LL, 1000LL);
            if (rnd.next(0, 1)) {
                y = x;
            }
            banks.push_back({x, y});
        }
    } else if (mode == 4) {
        while ((int)banks.size() < n) {
            if (rnd.next(0, 2) == 0) {
                banks.push_back(coprimePair(999900000LL, 1000000000LL));
            } else {
                banks.push_back({randomNearLimit(), rnd.next(1LL, 1000LL)});
            }
        }
    } else {
        while ((int)banks.size() < n) {
            long long lo = rnd.next(1LL, 1000000LL);
            long long hi = rnd.next(lo, min(1000000000LL, lo + rnd.next(0LL, 100000LL)));
            if (rnd.next(0, 1)) {
                banks.push_back(coprimePair(1, hi));
            } else {
                banks.push_back(nonCoprimePair(1, hi));
            }
        }
    }

    shuffle(banks.begin(), banks.end());

    println((int)banks.size());
    for (const Bank& bank : banks) {
        println(bank.first, bank.second);
    }

    return 0;
}
