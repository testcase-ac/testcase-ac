#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    int r;

    if (mode == 0) {
        k = rnd.next(1, 5);
        int n = 1 << k;
        r = rnd.next(1, n);
    } else if (mode == 1) {
        k = rnd.next(16, 20);
        int n = 1 << k;
        r = rnd.next(1, n);
    } else if (mode == 2) {
        k = rnd.next(1, 20);
        int n = 1 << k;
        r = rnd.any(vector<int>{1, 2, max(1, n - 1), n});
    } else if (mode == 3) {
        k = rnd.next(2, 20);
        int limit = 1 << k;
        int exponent = rnd.next(0, k);
        int base = 1 << exponent;
        r = min(limit, max(1, base + rnd.next(-2, 2)));
    } else if (mode == 4) {
        k = rnd.next(1, 20);
        int n = 1 << k;
        int band = max(1, n / rnd.next(2, 8));
        r = rnd.next(1, band);
        if (rnd.next(0, 1) == 1) {
            r = n - r + 1;
        }
    } else {
        k = rnd.next(1, 20);
        int n = 1 << k;
        r = rnd.next(1, n);
    }

    println(k, r);
    return 0;
}
