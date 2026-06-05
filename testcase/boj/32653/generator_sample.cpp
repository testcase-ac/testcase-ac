#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> values;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int x = rnd.next(1, 25);
        values.assign(n, x);
    } else if (mode == 1) {
        n = rnd.next(3, 15);
        vector<int> pool = {1, 2, 3, 4, 5, 6, 8, 10, 12, 16, 20, 24};
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        vector<int> pool = {7, 9, 11, 13, 15, 17, 19, 21, 23, 25};
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(pool));
        }
    } else if (mode == 3) {
        n = rnd.next(10, 35);
        int lo = rnd.next(1, 12);
        int hi = rnd.next(lo, 25);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        n = rnd.next(25, 80);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(1, 25));
        }
    } else {
        n = rnd.next(8, 25);
        values = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 25};
        while ((int)values.size() < n) {
            values.push_back(rnd.next(1, 25));
        }
        shuffle(values.begin(), values.end());
        values.resize(n);
    }

    println(n);
    println(values);

    return 0;
}
