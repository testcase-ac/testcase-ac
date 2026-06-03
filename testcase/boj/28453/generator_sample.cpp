#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clippedLevel(int x) {
    return max(1, min(300, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> levels;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        levels.push_back(rnd.any(vector<int>{1, 249, 250, 274, 275, 299, 300}));
    } else if (mode == 1) {
        for (int base : vector<int>{1, 249, 250, 274, 275, 300}) {
            int repeat = rnd.next(1, 3);
            for (int i = 0; i < repeat; ++i) {
                levels.push_back(base);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            int base = rnd.any(vector<int>{250, 275, 300});
            levels.push_back(clippedLevel(base + rnd.next(-3, 3)));
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 18);
        int lo = rnd.any(vector<int>{1, 250, 275});
        int hi = rnd.any(vector<int>{249, 274, 299, 300});
        if (lo > hi) {
            swap(lo, hi);
        }
        for (int i = 0; i < n; ++i) {
            levels.push_back(rnd.next(lo, hi));
        }
    } else {
        int n = rnd.next(10, 30);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 70) {
                levels.push_back(rnd.any(vector<int>{1, 249, 250, 274, 275, 299, 300}));
            } else {
                levels.push_back(rnd.next(1, 300));
            }
        }
    }

    shuffle(levels.begin(), levels.end());
    println(static_cast<int>(levels.size()));
    println(levels);

    return 0;
}
