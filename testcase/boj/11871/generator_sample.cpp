#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_P = 2147000000LL;

long long valueForGrundy(long long g, bool preferEven) {
    if (g <= 0) {
        return 1;
    }

    long long oddValue = 2 * g - 1;
    long long evenValue = 2 * (g + 1);
    if (preferEven && evenValue <= MAX_P) {
        return evenValue;
    }
    return min(oddValue, MAX_P);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<long long> p;

    if (mode == 0) {
        n = rnd.next(1, 10);
        p.resize(n);
        for (long long& x : p) {
            x = rnd.next(1, 20);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        p.assign(n, 2);
        int changes = rnd.next(1, min(n, 5));
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 0; i < changes; ++i) {
            p[order[i]] = rnd.any(vector<long long>{1, 3, 4, 5, 8, 9});
        }
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        p.resize(n);
        for (long long& x : p) {
            long long delta = rnd.next(0LL, 1000LL);
            x = MAX_P - delta;
            if (x < 1) {
                x = 1;
            }
        }
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        p.resize(n);
        int xr = 0;
        for (int i = 0; i + 1 < n; ++i) {
            int g = rnd.next(0, 1023);
            xr ^= g;
            p[i] = valueForGrundy(g, rnd.next(0, 1) == 1);
        }
        p[n - 1] = valueForGrundy(xr, rnd.next(0, 1) == 1);
    } else if (mode == 4) {
        n = rnd.next(3, 25);
        p.resize(n);
        long long base = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            long long step = rnd.next(0, 4);
            p[i] = min(MAX_P, base + step + i % 7);
        }
    } else {
        n = rnd.next(1, 100);
        p.resize(n);
        for (long long& x : p) {
            if (rnd.next(0, 9) < 7) {
                x = rnd.next(1, 30);
            } else {
                x = rnd.next(1LL, MAX_P);
            }
        }
    }

    if (all_of(p.begin(), p.end(), [](long long x) { return x == 2; })) {
        p[rnd.next(0, n - 1)] = 1;
    }

    println(n);
    println(p);
    return 0;
}
