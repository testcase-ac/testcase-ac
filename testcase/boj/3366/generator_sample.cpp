#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 30);
    if (mode == 0) n = rnd.next(1, 6);

    vector<long long> a(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a[i] = rnd.next(0, 10);
    } else if (mode == 1) {
        long long cur = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 8);
            a[i] = cur;
        }
    } else if (mode == 2) {
        long long cur = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 8);
            a[n - 1 - i] = cur;
        }
    } else if (mode == 3) {
        long long low = rnd.next(0, 50);
        long long high = rnd.next(100, 1000000000);
        for (int i = 0; i < n; ++i) a[i] = (i % 2 == 0 ? low : high);
        if (rnd.next(0, 1)) reverse(a.begin(), a.end());
    } else if (mode == 4) {
        long long base = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int dist = min(i, n - 1 - i);
            a[i] = base + 1LL * dist * rnd.next(1, 20);
        }
    } else if (mode == 5) {
        long long center = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int dist = min(i, n - 1 - i);
            a[i] = center + 1LL * (n - dist) * rnd.next(1, 20);
        }
    } else {
        long long cap = rnd.any(vector<long long>{1000LL, 1000000LL, 1000000000LL});
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 9) == 0) {
                a[i] = rnd.next(0, 1) ? 0 : 1000000000LL;
            } else {
                a[i] = rnd.next(0LL, cap);
            }
        }
    }

    println(n);
    for (long long x : a) println(x);

    return 0;
}
