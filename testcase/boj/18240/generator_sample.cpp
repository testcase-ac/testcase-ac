#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> depths;

    if (mode == 0) {
        n = rnd.next(2, 8);
        depths.assign(n - 1, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        depths.resize(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            depths[i] = i + 1;
        }
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        depths.resize(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            depths[i] = n - 1 - i;
        }
    } else if (mode == 3) {
        n = rnd.next(4, 20);
        depths.resize(n - 1);
        int cap = rnd.next(1, min(n - 1, 5));
        for (int i = 0; i < n - 1; ++i) {
            depths[i] = rnd.next(1, cap);
        }
    } else if (mode == 4) {
        n = rnd.next(4, 24);
        depths.resize(n - 1);
        int current = 1;
        for (int i = 0; i < n - 1; ++i) {
            if (i > 0 && current < n - 1 && rnd.next(0, 2) == 0) {
                ++current;
            }
            depths[i] = current;
        }
    } else if (mode == 5) {
        n = rnd.next(5, 28);
        depths.resize(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            depths[i] = rnd.next(1, n - 1);
        }
    } else if (mode == 6) {
        n = rnd.next(20, 80);
        depths.resize(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            int base = min(n - 1, i / 2 + 1);
            depths[i] = rnd.next(max(1, base - 2), min(n - 1, base + 2));
        }
        shuffle(depths.begin(), depths.end());
    } else {
        n = rnd.next(2, 300);
        depths.resize(n - 1);
        int low = max(1, n - rnd.next(1, min(n, 20)));
        for (int i = 0; i < n - 1; ++i) {
            depths[i] = rnd.next(low, n - 1);
        }
    }

    println(n);
    println(depths);

    return 0;
}
