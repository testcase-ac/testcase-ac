#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int nearValue(int center, int radius) {
    int lo = max(1, center - radius);
    int hi = min(1000000000, center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 3, 4, 5,
        999, 1000, 1001,
        9999999, 10000000, 10000001,
        906150257, 906150293, 906150294, 906150295,
        906154583, 906180359, 906209285, 906477701,
        999999997, 999999998, 999999999, 1000000000
    };

    int mode = rnd.next(0, 5);
    int t = mode == 0 ? rnd.next(0, 4) : rnd.next(6, 24);
    vector<int> values;

    for (int i = 0; i < t; ++i) {
        int kind = rnd.next(0, 5);
        int n;
        if (mode == 1 || kind == 0) {
            n = rnd.next(1, 1000);
        } else if (mode == 2 || kind == 1) {
            n = rnd.next(1, 10000000);
        } else if (kind == 2) {
            n = nearValue(rnd.any(anchors), rnd.next(0, 4));
        } else if (kind == 3) {
            n = rnd.next(1, 500000000) * 2;
        } else if (kind == 4) {
            n = rnd.next(0, 499999999) * 2 + 1;
        } else {
            n = rnd.next(1, 1000000000);
        }
        values.push_back(n);
    }

    if (!values.empty()) {
        values[rnd.next(static_cast<int>(values.size()))] = rnd.any(anchors);
        shuffle(values.begin(), values.end());
    }

    println(static_cast<int>(values.size()));
    for (int n : values) {
        println(n);
    }

    return 0;
}
