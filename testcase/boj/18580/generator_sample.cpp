#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(4, 16);
    } else if (mode == 3) {
        n = rnd.next(5, 18);
    } else if (mode == 4) {
        n = rnd.next(2, 20);
    } else {
        n = rnd.next(10, 30);
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);

    if (mode == 0) {
        // Already increasing.
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        int blockSize = rnd.next(1, max(1, n / 3));
        for (int l = 0; l < n; l += blockSize) {
            int r = min(n, l + blockSize);
            shuffle(p.begin() + l, p.begin() + r);
        }
    } else if (mode == 3) {
        int cut = rnd.next(1, n - 1);
        rotate(p.begin(), p.begin() + cut, p.end());
        if (rnd.next(0, 1)) {
            int l = rnd.next(0, n - 2);
            int r = rnd.next(l + 1, n - 1);
            reverse(p.begin() + l, p.begin() + r + 1);
        }
    } else if (mode == 4) {
        for (int i = 0; i + 1 < n; i += 2) {
            if (rnd.next(0, 1)) {
                swap(p[i], p[i + 1]);
            }
        }
        if (rnd.next(0, 1)) {
            shuffle(p.begin(), p.end());
        }
    } else {
        shuffle(p.begin(), p.end());
    }

    println(n);
    println(p);

    return 0;
}
