#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 6) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(1, 30);
    }

    int k;
    if (n == 1) {
        k = 1;
    } else {
        int kMode = rnd.next(0, 5);
        if (kMode == 0) {
            k = 1;
        } else if (kMode == 1) {
            k = n;
        } else if (kMode == 2) {
            k = 2;
        } else if (kMode == 3) {
            k = (n + 1) / 2;
        } else {
            k = rnd.next(1, n);
        }
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }

    if (mode == 0) {
        shuffle(a.begin(), a.end());
    } else if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        vector<int> b;
        int lo = 1, hi = n;
        while (lo <= hi) {
            if (rnd.next(0, 1)) {
                b.push_back(hi--);
                if (lo <= hi) b.push_back(lo++);
            } else {
                b.push_back(lo++);
                if (lo <= hi) b.push_back(hi--);
            }
        }
        a = b;
    } else if (mode == 3) {
        int shift = rnd.next(0, n - 1);
        rotate(a.begin(), a.begin() + shift, a.end());
    } else if (mode == 4 && n > 1) {
        int block = rnd.next(2, min(n, 8));
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            shuffle(a.begin() + l, a.begin() + r);
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 5) {
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) {
            positions[i] = i;
        }
        shuffle(positions.begin(), positions.end());
        vector<int> b(n);
        for (int value = 1; value <= n; ++value) {
            b[positions[value - 1]] = value;
        }
        a = b;
    } else {
        int block = rnd.next(3, 12);
        for (int l = 0; l < n; l += block) {
            int r = min(n, l + block);
            if (rnd.next(0, 1)) {
                reverse(a.begin() + l, a.begin() + r);
            } else {
                shuffle(a.begin() + l, a.begin() + r);
            }
        }
        int swaps = rnd.next(1, max(1, n / 5));
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(0, n - 1)], a[rnd.next(0, n - 1)]);
        }
    }

    println(n, k);
    println(a);
    return 0;
}
