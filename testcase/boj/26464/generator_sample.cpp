#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<int> a(n);

    if (mode == 0) {
        int hi = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, hi);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = i + 1;
        }
        int swaps = rnd.next(0, n);
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(0, n - 1)], a[rnd.next(0, n - 1)]);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = n - i;
        }
        int swaps = rnd.next(0, n);
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(0, n - 1)], a[rnd.next(0, n - 1)]);
        }
    } else if (mode == 3) {
        int lo = rnd.next(1, n);
        int hi = rnd.next(lo, n);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? lo : hi;
        }
        int changes = rnd.next(0, n);
        for (int i = 0; i < changes; ++i) {
            a[rnd.next(0, n - 1)] = rnd.next(lo, hi);
        }
    } else if (mode == 4) {
        int block = rnd.next(1, min(n, 6));
        for (int i = 0; i < n; ++i) {
            a[i] = min(n, i / block + 1);
        }
        if (rnd.next(0, 1) == 1) {
            reverse(a.begin(), a.end());
        }
    } else {
        int pivot = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            if (i < pivot) {
                a[i] = rnd.next(1, max(1, n / 2));
            } else {
                a[i] = rnd.next(max(1, n / 2), n);
            }
        }
        if (rnd.next(0, 1) == 1) {
            reverse(a.begin(), a.end());
        }
    }

    println(n);
    println(a);

    return 0;
}
