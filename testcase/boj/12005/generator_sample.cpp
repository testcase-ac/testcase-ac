#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampSize(int x) {
    return max(1, min(10000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int k;
    vector<int> diamonds;

    if (mode == 0) {
        k = 0;
        int distinct = rnd.next(1, min(n, 6));
        vector<int> values;
        for (int i = 0; i < distinct; ++i) {
            values.push_back(rnd.next(1, 10000));
        }
        for (int i = 0; i < n; ++i) {
            diamonds.push_back(rnd.any(values));
        }
    } else if (mode == 1) {
        k = rnd.next(1, 8);
        int base = rnd.next(1, 10000 - k);
        for (int i = 0; i < n; ++i) {
            diamonds.push_back(base + rnd.next(0, k));
        }
    } else if (mode == 2) {
        k = rnd.next(1, 20);
        int base = rnd.next(1, 10000 - min(9000, 3 * k + 20));
        int gap = k + rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int cluster = rnd.next(0, 2);
            diamonds.push_back(clampSize(base + cluster * gap + rnd.next(0, k)));
        }
    } else if (mode == 3) {
        k = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                diamonds.push_back(rnd.next(1, min(10000, k + 2)));
            } else {
                diamonds.push_back(rnd.next(max(1, 9999 - k), 10000));
            }
        }
    } else if (mode == 4) {
        k = 10000;
        for (int i = 0; i < n; ++i) {
            diamonds.push_back(rnd.next(1, 10000));
        }
    } else {
        k = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) {
            diamonds.push_back(rnd.next(1, 10000));
        }
    }

    shuffle(diamonds.begin(), diamonds.end());

    println(n, k);
    for (int x : diamonds) {
        println(x);
    }

    return 0;
}
