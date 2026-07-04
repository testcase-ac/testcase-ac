#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 40);
    if (rnd.next(8) == 0) {
        n = rnd.next(41, 200);
    }

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i + 1;
    }

    int mode = rnd.next(6);
    if (mode == 0) {
        // Already sorted.
    } else if (mode == 1) {
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        int shift = rnd.next(0, n - 1);
        rotate(p.begin(), p.begin() + shift, p.end());
    } else if (mode == 3) {
        int blockSize = rnd.next(1, max(1, min(n, 8)));
        for (int l = 0; l < n; l += blockSize) {
            int r = min(n, l + blockSize);
            reverse(p.begin() + l, p.begin() + r);
        }
    } else if (mode == 4) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            swap(p[a], p[b]);
        }
    } else {
        shuffle(p.begin(), p.end());
    }

    println(n);
    println(p);
    return 0;
}
