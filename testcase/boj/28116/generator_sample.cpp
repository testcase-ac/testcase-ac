#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (rnd.next(100) < 85) {
        n = rnd.next(2, 25);
    } else {
        n = rnd.next(26, 80);
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }

    if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        int shift = rnd.next(1, n - 1);
        rotate(a.begin(), a.begin() + shift, a.end());
    } else if (mode == 3) {
        for (int i = 0; i + 1 < n; i += 2) {
            if (rnd.next(100) < 80) {
                swap(a[i], a[i + 1]);
            }
        }
    } else if (mode == 4) {
        int block = rnd.next(2, min(n, 8));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            reverse(a.begin() + l, a.begin() + r);
        }
        if (rnd.next(2)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 5) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int it = 0; it < swaps; ++it) {
            int i = rnd.next(0, n - 1);
            int j = rnd.next(0, n - 1);
            swap(a[i], a[j]);
        }
    } else if (mode == 6) {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
