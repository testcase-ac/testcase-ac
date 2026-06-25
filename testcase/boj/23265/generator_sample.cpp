#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, mode == 6 ? 80 : 30);
    int c = 1;
    vector<int> x(n);

    if (mode == 0) {
        c = rnd.next(1, 5);
        int base = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) x[i] = base;
    } else if (mode == 1) {
        c = rnd.next(1, 20);
        int start = rnd.next(1, 1000000);
        int step = rnd.next(0, 2 * c + 5);
        for (int i = 0; i < n; ++i) {
            long long value = start + 1LL * i * step;
            x[i] = int(min(1000000LL, value));
        }
    } else if (mode == 2) {
        c = rnd.next(1, 20);
        int start = rnd.next(1, 1000000);
        int step = rnd.next(0, 2 * c + 5);
        for (int i = 0; i < n; ++i) {
            long long value = start - 1LL * i * step;
            x[i] = int(max(1LL, value));
        }
    } else if (mode == 3) {
        c = rnd.next(1, 30);
        int low = rnd.next(1, 100);
        int high = rnd.next(999900, 1000000);
        for (int i = 0; i < n; ++i) x[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 4) {
        c = rnd.next(1, 1000000);
        int lo = rnd.next(1, 1000000);
        int hi = rnd.next(lo, 1000000);
        for (int i = 0; i < n; ++i) x[i] = rnd.next(lo, hi);
    } else if (mode == 5) {
        c = rnd.next(1, 50);
        int base = rnd.next(100, 999900);
        for (int i = 0; i < n; ++i) {
            int drift = i * rnd.next(0, c + 3);
            int noise = rnd.next(-80, 80);
            x[i] = max(1, min(1000000, base + drift + noise));
        }
    } else {
        c = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                x[i] = rnd.next(1, 1000000);
            } else {
                x[i] = rnd.any(vector<int>{1, 2, 999999, 1000000});
            }
        }
    }

    println(n, c);
    println(x);
    return 0;
}
