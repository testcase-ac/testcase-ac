#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 60);
    vector<int> a(n);

    if (mode == 0) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            a[i] = value;
        }
    } else if (mode == 1) {
        int first = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            a[i] = first ^ (i % 2);
        }
    } else if (mode == 2) {
        int prefix = rnd.next(0, n);
        int flipRate = rnd.next(5, 35);
        for (int i = 0; i < n; ++i) {
            a[i] = (i < prefix ? 1 : 0);
            if (rnd.next(1, 100) <= flipRate) {
                a[i] ^= 1;
            }
        }
    } else if (mode == 3) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < n;) {
            int len = rnd.next(1, 8);
            for (int j = 0; j < len && i < n; ++j, ++i) {
                a[i] = value;
            }
            value ^= 1;
        }
    } else if (mode == 4) {
        int onesPercent = rnd.next(10, 90);
        for (int i = 0; i < n; ++i) {
            a[i] = (rnd.next(1, 100) <= onesPercent ? 1 : 0);
        }
    } else {
        int left = rnd.next(0, n - 1);
        int right = rnd.next(left, n - 1);
        for (int i = left; i <= right; ++i) {
            a[i] = 1;
        }
        if (rnd.next(0, 1) == 1) {
            for (int i = 0; i < n; ++i) {
                a[i] ^= 1;
            }
        }
    }

    println(n);
    println(a);

    return 0;
}
