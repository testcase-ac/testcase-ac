#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> b;

    if (mode == 0) {
        n = 1;
        b.push_back(rnd.next(1, 100000));
    } else if (mode == 1) {
        n = rnd.next(2, 15);
        int value = rnd.next(1, 100000);
        b.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 15);
        int small = rnd.next(1, 50000);
        int large = rnd.next(small + 1, 100000);
        for (int i = 0; i < n; ++i) {
            b.push_back(i % 2 == 0 ? small : large);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        int value = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            value += rnd.next(1, 20);
            b.push_back(value);
        }
    } else if (mode == 4) {
        n = rnd.next(4, 15);
        vector<int> base = {1, 2, 4, 8, 16, 32, 64};
        for (int i = 0; i < n; ++i) {
            int value = base[rnd.next(0, (int)base.size() - 1)] * rnd.next(1, 40);
            b.push_back(min(value, 100000));
        }
    } else if (mode == 5) {
        n = rnd.next(10, 15);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                b.push_back(rnd.next(99900, 100000));
            } else {
                b.push_back(rnd.next(1, 100));
            }
        }
    } else {
        n = rnd.next(2, 15);
        int lo = rnd.next(1, 90000);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 1000)));
        for (int i = 0; i < n; ++i) {
            b.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(b.begin(), b.end());

    println(n);
    println(b);
    return 0;
}
