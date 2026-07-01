#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 25);

    long long a = rnd.next(1, 20);
    long long b = rnd.next(1, 20);
    long long x = rnd.next(1, 50);
    long long y = rnd.next(1, 50);

    if (mode == 1) {
        a = rnd.next(15, 80);
        b = rnd.next(15, 80);
        x = rnd.next(1, 10);
        y = rnd.next(1, 10);
    } else if (mode == 2) {
        a = rnd.next(1, 5);
        b = rnd.next(20, 100);
        x = rnd.next(1, 10);
        y = rnd.next(30, 100);
    } else if (mode == 3) {
        a = rnd.next(20, 100);
        b = rnd.next(1, 5);
        x = rnd.next(30, 100);
        y = rnd.next(1, 10);
    } else if (mode == 4) {
        n = rnd.next(40, 80);
        a = rnd.next(1, 1000000000);
        b = rnd.next(1, 1000000000);
        x = rnd.next(1, 1000000000);
        y = rnd.next(1, 1000000000);
    } else if (mode == 5) {
        a = rnd.any(vector<long long>{1, 2, 1000000000LL});
        b = rnd.any(vector<long long>{1, 2, 1000000000LL});
        x = rnd.any(vector<long long>{1, 1000000000LL});
        y = rnd.any(vector<long long>{1, 1000000000LL});
    }

    vector<long long> times(n);
    long long cur = rnd.next(1, 5);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            long long gap;
            if (mode == 1 || mode == 5) {
                gap = rnd.next(1, 3);
            } else if (mode == 4) {
                gap = rnd.next(1, 1000000);
            } else {
                long long cap = max(2LL, min({a, b, 100LL}));
                gap = rnd.next(1LL, cap);
            }
            cur += gap;
        }
        times[i] = cur;
    }

    long long maxTime = 1000000000LL;
    if (times.back() > maxTime) {
        long long shift = times.back() - maxTime;
        for (long long& t : times) t -= shift;
    }

    vector<int> types(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            types[i] = rnd.next(1, 3);
        } else if (mode == 1) {
            types[i] = (i % 2) + 1;
        } else if (mode == 2) {
            types[i] = rnd.next(1, 100) <= 70 ? 2 : 3;
        } else if (mode == 3) {
            types[i] = rnd.next(1, 100) <= 70 ? 1 : 3;
        } else if (mode == 4) {
            types[i] = rnd.any(vector<int>{1, 2, 3, 3});
        } else {
            types[i] = 3;
        }
    }

    println(n, a, b, x, y);
    for (int i = 0; i < n; ++i) {
        println(times[i], types[i]);
    }

    return 0;
}
