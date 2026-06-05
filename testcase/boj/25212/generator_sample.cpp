#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> c;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 10);
        int lo = rnd.next(2, 12);
        int hi = rnd.next(lo, 25);
        for (int i = 0; i < n; ++i) c.push_back(rnd.next(lo, hi));
    } else if (mode == 1) {
        int n = rnd.next(1, 10);
        int value = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) c.push_back(value);
    } else if (mode == 2) {
        vector<vector<int>> bases = {
            {2, 3, 6},
            {2, 4, 4},
            {3, 3, 3},
            {4, 4, 4, 4},
            {5, 5, 5, 5, 5},
            {2, 4, 8, 8},
            {2, 5, 10, 10},
        };
        c = rnd.any(bases);
        int extra = rnd.next(0, 10 - int(c.size()));
        for (int i = 0; i < extra; ++i) c.push_back(rnd.next(6, 25));
    } else if (mode == 3) {
        int n = rnd.next(2, 10);
        int small = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            c.push_back(rnd.next() < 0.65 ? small : rnd.next(7, 25));
        }
    } else if (mode == 4) {
        int n = rnd.next(6, 10);
        for (int i = 0; i < n; ++i) c.push_back(rnd.next(18, 25));
    } else {
        vector<int> pool = {2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24};
        int n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) c.push_back(rnd.any(pool));
    }

    shuffle(c.begin(), c.end());
    println(int(c.size()));
    println(c);

    return 0;
}
