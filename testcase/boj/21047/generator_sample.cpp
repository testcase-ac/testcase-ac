#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long pow10int(int e) {
    long long v = 1;
    for (int i = 0; i < e; ++i) {
        v *= 10;
    }
    return v;
}

long long randomValueInDigits(int digits) {
    if (digits == 1) {
        return rnd.next(0LL, 9LL);
    }
    long long lo = pow10int(digits - 1);
    long long hi = min(1000000000000000LL, pow10int(digits) - 1);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<long long> a;

    if (mode == 0) {
        int digits = rnd.next(1, 16);
        long long x = randomValueInDigits(digits);
        n = rnd.next(2, 10);
        a.assign(n, x);
    } else if (mode == 1) {
        int digits = rnd.next(2, 16);
        long long base = pow10int(digits - 1);
        n = rnd.next(2, 8);
        long long start = max(0LL, base - rnd.next(0LL, 3LL));
        for (int i = 0; i < n; ++i) {
            a.push_back(min(1000000000000000LL, start + rnd.next(0LL, 6LL)));
        }
        sort(a.begin(), a.end());
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        long long cur = rnd.next(0LL, 20LL);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 99) < 45) {
                a.push_back(cur);
            } else {
                cur += rnd.next(0LL, 12LL);
                a.push_back(cur);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            int digits = rnd.next(1, 16);
            a.push_back(randomValueInDigits(digits));
        }
        a.push_back(1000000000000000LL);
        sort(a.begin(), a.end());
        n = (int)a.size();
    } else if (mode == 4) {
        vector<long long> pool = {
            0LL,
            1LL,
            9LL,
            10LL,
            11LL,
            99LL,
            100LL,
            9999999LL,
            999999999999999LL,
            1000000000000000LL,
        };
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
        sort(a.begin(), a.end());
    } else {
        n = rnd.next(2, 20);
        long long lo = rnd.next(0LL, 1000000LL);
        long long hi = rnd.next(lo, 1000000000000000LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
        sort(a.begin(), a.end());
    }

    println((int)a.size());
    println(a);

    return 0;
}
