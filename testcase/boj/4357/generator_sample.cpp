#include "testlib.h"
#include <vector>

using namespace std;

static long long modPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

static void addCase(vector<vector<long long>>& cases, long long p, long long b, long long n) {
    cases.push_back({p, b, n});
}

static void addSolvedCase(vector<vector<long long>>& cases, long long p, long long b, long long exp) {
    addCase(cases, p, b, modPow(b, exp, p));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<long long> smallPrimes = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    const vector<long long> mediumPrimes = {101, 257, 1009, 10007, 65537, 104729, 999983};
    const vector<long long> largePrimes = {12345701, 1000000007, 1073741827, 2147483647};

    vector<vector<long long>> cases;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        long long p = rnd.any(smallPrimes);
        int maxCount = (int)min<long long>(12, 2 * (p - 2));
        int count = rnd.next(1, maxCount);
        for (int i = 0; i < count; ++i) {
            long long b = rnd.next(2LL, p - 1);
            long long n = rnd.next(1LL, p - 1);
            addCase(cases, p, b, n);
        }
    } else if (mode == 1) {
        long long p = rnd.any(mediumPrimes);
        int count = rnd.next(3, 8);
        for (int i = 0; i < count; ++i) {
            long long b = rnd.next(2LL, p - 1);
            long long exp = rnd.wnext((int)min(100000LL, p - 1), 2);
            addSolvedCase(cases, p, b, exp);
        }
    } else if (mode == 2) {
        long long p = rnd.any(mediumPrimes);
        int count = rnd.next(3, 7);
        for (int i = 0; i < count; ++i) {
            long long b = rnd.next(2LL, p - 1);
            long long n = rnd.next(1LL, p - 1);
            addCase(cases, p, b, n);
        }
    } else if (mode == 3) {
        long long p = rnd.any(largePrimes);
        int count = rnd.next(2, 4);
        for (int i = 0; i < count; ++i) {
            long long b;
            if (rnd.next(0, 2) == 0) {
                b = 2;
            } else if (rnd.next(0, 1) == 0) {
                b = p - 1;
            } else {
                b = rnd.next(2LL, min(1000000LL, p - 1));
            }

            if (rnd.next(0, 1) == 0) {
                addSolvedCase(cases, p, b, rnd.next(0LL, min(1000000LL, p - 2)));
            } else {
                addCase(cases, p, b, rnd.next(1LL, p - 1));
            }
        }
    } else {
        addCase(cases, 3, 2, rnd.next(1LL, 2LL));
        addCase(cases, 5, rnd.next(2LL, 4LL), rnd.next(1LL, 4LL));
        addSolvedCase(cases, 2147483647, 2147483646, rnd.next(0LL, 1LL));
    }

    shuffle(cases.begin(), cases.end());
    for (const auto& c : cases) {
        println(c[0], c[1], c[2]);
    }

    return 0;
}
