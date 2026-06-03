#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxValue = 2147483647;

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 32);
    } else if (mode == 3) {
        n = 1 << rnd.next(1, 7);
    } else if (mode == 4) {
        n = rnd.next(33, 120);
    } else {
        n = rnd.next(121, 300);
    }

    int q = rnd.next(1, min(300, max(1, 3 * n + 20)));

    vector<int> values(n);
    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (valueMode == 0) {
            values[i] = rnd.next(0, 15);
        } else if (valueMode == 1) {
            values[i] = rnd.next(0, 1023);
        } else if (valueMode == 2) {
            values[i] = rnd.next(0, maxValue);
        } else if (valueMode == 3) {
            values[i] = (i % 2 == 0 ? 0 : maxValue);
        } else {
            values[i] = rnd.next(0, 1) ? (1 << rnd.next(0, 30)) : rnd.next(0, 255);
        }
    }

    println(n);
    println(values);
    println(q);

    int firstTypeOne = rnd.next(1, q);
    for (int qi = 1; qi <= q; ++qi) {
        bool mustQuery = qi == firstTypeOne;
        bool emitQuery = mustQuery || rnd.next(0, 99) < 65;

        if (emitQuery) {
            int l;
            int r;
            int rangeMode = rnd.next(0, 4);
            if (rangeMode == 0) {
                l = 0;
                r = n - 1;
            } else if (rangeMode == 1) {
                l = rnd.next(0, n - 1);
                r = l;
            } else if (rangeMode == 2) {
                l = rnd.next(0, n - 1);
                int width = rnd.next(0, min(n - 1 - l, 5));
                r = l + width;
            } else if (rangeMode == 3) {
                r = rnd.next(0, n - 1);
                l = rnd.next(max(0, r - 5), r);
            } else {
                l = rnd.next(0, n - 1);
                r = rnd.next(l, n - 1);
            }

            int x;
            int xMode = rnd.next(0, 4);
            if (xMode == 0) {
                x = 0;
            } else if (xMode == 1) {
                x = n - 1;
            } else if (xMode == 2) {
                x = rnd.next(0, min(n - 1, 15));
            } else if (xMode == 3) {
                int bit = rnd.next(0, 30);
                x = min(n - 1, 1 << bit);
            } else {
                x = rnd.next(0, n - 1);
            }

            println(1, l, r, x);
        } else {
            int i = rnd.next(0, n - 1);
            int updateMode = rnd.next(0, 4);
            int x;
            if (updateMode == 0) {
                x = 0;
            } else if (updateMode == 1) {
                x = maxValue;
            } else if (updateMode == 2) {
                x = rnd.next(0, 255);
            } else if (updateMode == 3) {
                x = 1 << rnd.next(0, 30);
            } else {
                x = rnd.next(0, maxValue);
            }
            println(2, i, x);
        }
    }

    return 0;
}
