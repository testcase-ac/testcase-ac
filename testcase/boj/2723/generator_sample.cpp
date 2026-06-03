#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<int> values;

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(1, 11));
        }
    } else if (mode == 1) {
        int n = rnd.next(6, 20);
        vector<int> pool = {1, 2, 3, 9, 10, 11};
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        int n = rnd.next(1, 100);
        int b = rnd.next(1, 11);
        values.assign(n, b);
    } else if (mode == 3) {
        int n = rnd.next(11, 100);
        for (int i = 0; i < n; ++i) {
            values.push_back(i % 11 + 1);
        }
        shuffle(values.begin(), values.end());
    } else {
        int n = rnd.next(50, 100);
        int lo = rnd.next(1, 11);
        int hi = rnd.next(lo, 11);
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.next(lo, hi));
        }
    }

    println(static_cast<int>(values.size()));
    for (int b : values) {
        println(b);
    }

    return 0;
}
