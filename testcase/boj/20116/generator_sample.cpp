#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int X_MIN = -1000000000;
const int X_MAX = 1000000000;

int clampX(long long x) {
    return (int)max((long long)X_MIN, min((long long)X_MAX, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    int L = rnd.next(1, 30);
    vector<int> x(n);

    if (mode == 0) {
        L = rnd.any(vector<int>{1, 2, 10, 1000000000});
        x[0] = rnd.next(-20, 20);
        n = 1;
    } else if (mode == 1) {
        L = rnd.next(1, 1000000);
        int center = rnd.next(-1000000, 1000000);
        fill(x.begin(), x.end(), center);
    } else if (mode == 2) {
        L = rnd.next(2, 40);
        int current = rnd.next(-1000, 1000);
        x[n - 1] = current;
        for (int i = n - 2; i >= 0; --i) {
            int delta = rnd.next(-(L - 1), L - 1);
            x[i] = clampX(current + delta);
            current = (current + x[i]) / 2;
        }
    } else if (mode == 3) {
        L = rnd.next(1, 100);
        int top = rnd.next(-1000, 1000);
        fill(x.begin(), x.end(), top);
        x[0] = clampX((long long)top + rnd.any(vector<int>{-L, L}));
    } else if (mode == 4) {
        L = rnd.next(1, 100);
        int base = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            int direction = (i % 2 == 0 ? -1 : 1);
            x[i] = clampX((long long)base + direction * rnd.next(L, 3 * L + 20));
        }
    } else {
        L = rnd.any(vector<int>{1, 2, 3, 10, 1000000000});
        int lo = rnd.next(-1000000000, 999999900);
        int hi = rnd.next(lo, min(X_MAX, lo + rnd.next(0, 100)));
        for (int i = 0; i < n; ++i) x[i] = rnd.next(lo, hi);
    }

    x.resize(n);
    println(n, L);
    println(x);
    return 0;
}
