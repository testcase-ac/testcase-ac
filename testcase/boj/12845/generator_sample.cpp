#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> levels;

    if (mode == 0) {
        n = 1;
        levels.push_back(rnd.next(1, 100000));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int value = rnd.next(1, 100000);
        levels.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        int lo = rnd.next(1, 200);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 5000)));
        for (int i = 0; i < n; ++i) {
            levels.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            levels.push_back(rnd.next(1, 100000));
        }
        sort(levels.begin(), levels.end());
        if (rnd.next(0, 1)) {
            reverse(levels.begin(), levels.end());
        }
    } else if (mode == 4) {
        n = rnd.next(3, 25);
        levels.assign(n, rnd.next(1, 100));
        int pos = rnd.next(0, n - 1);
        levels[pos] = rnd.next(50000, 100000);
        for (int i = 0; i < n; ++i) {
            if (i != pos && rnd.next(0, 3) == 0) {
                levels[i] = rnd.next(1, 100000);
            }
        }
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        vector<int> palette;
        int paletteSize = rnd.next(2, 5);
        for (int i = 0; i < paletteSize; ++i) {
            palette.push_back(rnd.next(1, 100000));
        }
        for (int i = 0; i < n; ++i) {
            levels.push_back(rnd.any(palette));
        }
    } else if (mode == 6) {
        n = rnd.next(10, 40);
        for (int i = 0; i < n; ++i) {
            levels.push_back((i % 2 == 0) ? rnd.next(1, 20) : rnd.next(99980, 100000));
        }
    } else {
        n = rnd.next(40, 80);
        for (int i = 0; i < n; ++i) {
            levels.push_back(rnd.next(1, 100000));
        }
    }

    if (mode != 3 && mode != 6 && rnd.next(0, 1)) {
        shuffle(levels.begin(), levels.end());
    }

    println(n);
    println(levels);

    return 0;
}
