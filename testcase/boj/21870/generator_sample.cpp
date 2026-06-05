#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(long long value) {
    return static_cast<int>(max(1LL, min(200000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(1, 200000));
    } else if (mode == 1) {
        n = 1 << rnd.next(1, 5);
        int value = rnd.next(1, 200000);
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 25);
        int base = rnd.next(1, 2000);
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 100);
            a.push_back(boundedValue(1LL * base * multiplier));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 31);
        if (n % 2 == 0) ++n;
        int leftGcd = rnd.next(2, 400);
        int rightGcd = rnd.next(2, 400);
        for (int i = 0; i < n; ++i) {
            int g = (i < n / 2 ? leftGcd : rightGcd);
            a.push_back(boundedValue(1LL * g * rnd.next(1, 120)));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        int hi = rnd.next(2, 200000);
        int lo = rnd.next(1, hi);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        int common = rnd.next(2, 1000);
        for (int i = 0; i < n; ++i) {
            int noise = (i % 2 == 0 ? common : rnd.next(1, 1000));
            a.push_back(boundedValue(1LL * noise * rnd.next(1, 120)));
        }
    } else if (mode == 6) {
        n = rnd.next(2, 30);
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        for (int i = 0; i < n; ++i) {
            int p = rnd.any(primes);
            int q = rnd.any(primes);
            a.push_back(boundedValue(1LL * p * q * rnd.next(1, 80)));
        }
    } else {
        n = rnd.next(2, 31);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(1, 200000);
            if (rnd.next(0, 4) == 0) value = 1;
            if (rnd.next(0, 5) == 0) value = 200000;
            a.push_back(value);
        }
    }

    if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    if (rnd.next(0, 3) == 0) shuffle(a.begin(), a.end());

    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
