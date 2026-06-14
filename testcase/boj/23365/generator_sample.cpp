#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> d;

    if (mode == 0) {
        n = 2;
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 100);
        d = {lo, hi};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int value = rnd.next(1, 1000000000);
        d.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        d.resize(n);
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) d[i] = base + rnd.next(0, 5);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        d.resize(n);
        for (int i = 0; i < n; ++i) {
            d[i] = (rnd.next(0, 1) == 0) ? rnd.next(1, 10) : rnd.next(999999990, 1000000000);
        }
    } else if (mode == 4) {
        n = rnd.next(10, 40);
        d.resize(n);
        int upper = rnd.next(20, 500);
        for (int i = 0; i < n; ++i) d[i] = rnd.next(1, upper);
        sort(d.begin(), d.end());
        if (rnd.next(0, 1) == 0) reverse(d.begin(), d.end());
    } else {
        n = rnd.next(2, 30);
        d.resize(n);
        int cap = rnd.next(1000, 1000000);
        for (int i = 0; i < n; ++i) d[i] = rnd.next(1, cap);
    }

    if (rnd.next(0, 2) != 0) shuffle(d.begin(), d.end());

    println(n);
    println(d);
    return 0;
}
