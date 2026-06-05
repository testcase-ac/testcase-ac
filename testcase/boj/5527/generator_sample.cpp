#include "testlib.h"

#include <vector>

using namespace std;

int originalState(int normalized, int index) {
    return normalized ^ (index % 2 == 0 ? 1 : 0);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(1000, 100000);
    } else if (rnd.next(0, 9) == 0) {
        n = rnd.next(2, 3);
    } else {
        n = rnd.next(4, 40);
    }

    vector<int> a(n);

    if (mode == 0) {
        int first = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            a[i] = first ^ (i % 2);
        }
    } else if (mode == 1) {
        int value = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            a[i] = value;
        }
    } else if (mode == 2) {
        int bias = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 10) <= bias ? 1 : 0;
        }
    } else {
        int cur = rnd.next(0, 1);
        int i = 0;
        while (i < n) {
            int maxLen = mode == 3 ? 6 : 20;
            int len = rnd.next(1, maxLen);
            if (mode == 4 && rnd.next(0, 3) == 0) {
                len = rnd.next(1, n - i);
            }
            for (int j = 0; j < len && i < n; ++j, ++i) {
                a[i] = originalState(cur, i);
            }
            cur ^= 1;
        }

        if (mode == 5) {
            for (int flips = rnd.next(1, 20); flips > 0; --flips) {
                int pos = rnd.next(0, n - 1);
                a[pos] ^= 1;
            }
        }
    }

    println(n);
    println(a);

    return 0;
}
