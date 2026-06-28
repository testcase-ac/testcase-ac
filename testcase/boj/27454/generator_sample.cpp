#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    int k = rnd.next(2, n + 1);
    long long y = rnd.next(1LL, 1000000000LL);
    vector<long long> v(n);

    if (mode == 0) {
        long long base = rnd.next(1LL, 1000000000LL);
        int spread = rnd.next(0, 5);
        for (long long& x : v) {
            x = min(1000000000LL, max(1LL, base + rnd.next(-spread, spread)));
        }
        y = min(1000000000LL, max(1LL, base + rnd.next(-spread, spread)));
    } else if (mode == 1) {
        y = rnd.next(5LL, 999999995LL);
        int spread = rnd.next(1, 20);
        for (long long& x : v) {
            x = min(1000000000LL, max(1LL, y + rnd.next(-spread, spread)));
        }
    } else if (mode == 2) {
        vector<long long> choices = {1LL, 2LL, y, 999999999LL, 1000000000LL};
        for (long long& x : v) {
            x = choices[rnd.next(0, int(choices.size()) - 1)];
        }
    } else if (mode == 3) {
        long long low = rnd.next(1LL, 200LL);
        long long high = rnd.next(999999800LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            v[i] = (i % 2 == 0) ? low + rnd.next(0LL, 50LL) : high - rnd.next(0LL, 50LL);
        }
        y = rnd.next(0, 1) ? low : high;
    } else if (mode == 4) {
        long long start = rnd.next(1LL, 999999900LL);
        long long step = rnd.next(1LL, 20LL);
        for (int i = 0; i < n; ++i) {
            v[i] = min(1000000000LL, start + step * i);
        }
        y = v[rnd.next(0, n - 1)];
    } else {
        n = rnd.next(8, 30);
        k = rnd.next(2, n + 1);
        v.resize(n);
        long long left = rnd.next(1LL, 1000LL);
        long long right = rnd.next(1000000LL, 1000000000LL);
        for (int i = 0; i < n; ++i) {
            v[i] = (rnd.next(0, 2) == 0) ? left + rnd.next(0LL, 100LL)
                                          : right - rnd.next(0LL, 100LL);
        }
        y = rnd.next(0, 1) ? left + rnd.next(0LL, 100LL)
                           : right - rnd.next(0LL, 100LL);
    }

    if (rnd.next(0, 3) == 0) {
        sort(v.begin(), v.end());
    } else if (rnd.next(0, 2) == 0) {
        sort(v.rbegin(), v.rend());
    } else {
        shuffle(v.begin(), v.end());
    }

    println(n, k);
    println(y);
    println(v);
    return 0;
}
