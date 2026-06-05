#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(2, 45);
    if (rnd.next(100) < 10) {
        n = rnd.next(46, 120);
    }

    vector<int> a(n);

    if (mode == 0) {
        int start = rnd.next(1, 5000 - n + 1);
        for (int i = 0; i < n; ++i) {
            a[i] = start + i;
        }
    } else if (mode == 1) {
        int start = rnd.next(n, 5000);
        for (int i = 0; i < n; ++i) {
            a[i] = start - i;
        }
    } else if (mode == 2) {
        int value = rnd.next(1, 5000);
        for (int i = 0; i < n; ++i) {
            a[i] = value;
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, 4995);
        int hi = rnd.next(lo, min(5000, lo + rnd.next(1, 8)));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    } else if (mode == 4) {
        int low = rnd.next(1, 50);
        int high = rnd.next(4950, 5000);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0 ? low + rnd.next(0, 20) : high - rnd.next(0, 20));
        }
    } else if (mode == 5) {
        int blockSize = rnd.next(2, 7);
        int value = rnd.next(1, 5000);
        int step = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            if (i % blockSize == 0 && i > 0) {
                value = min(5000, value + step + rnd.next(0, 3));
            }
            a[i] = value;
        }
        if (rnd.next(2)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 6) {
        int alphabet = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            a[i] = 1 + rnd.next(alphabet);
        }
        shuffle(a.begin(), a.end());
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 5000);
        }
    }

    println(n);
    println(a);

    return 0;
}
