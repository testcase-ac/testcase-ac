#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampK(long long value) {
    if (value < 1) return 1;
    if (value > 1000000000LL) return 1000000000;
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int t = rnd.next(1, 60);
    vector<int> values;
    values.reserve(t);

    if (mode == 0) {
        t = rnd.next(1, 20);
        for (int i = 0; i < t; ++i) {
            values.push_back(rnd.next(1, 40));
        }
    } else if (mode == 1) {
        vector<int> anchors = {1, 2, 3, 4, 5, 10, 25, 100, 999999999, 1000000000};
        t = rnd.next(5, 30);
        for (int i = 0; i < t; ++i) {
            int anchor = rnd.any(anchors);
            int delta = rnd.next(-3, 3);
            values.push_back(clampK(1LL * anchor + delta));
        }
    } else if (mode == 2) {
        t = rnd.next(8, 45);
        int base = rnd.next(1, 1000000000);
        int span = rnd.next(0, 200);
        for (int i = 0; i < t; ++i) {
            values.push_back(clampK(1LL * base + rnd.next(-span, span)));
        }
    } else if (mode == 3) {
        t = rnd.next(8, 50);
        vector<int> factors = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        for (int i = 0; i < t; ++i) {
            long long k = 1;
            int steps = rnd.next(0, 12);
            for (int j = 0; j < steps; ++j) {
                long long next = k * rnd.any(factors);
                if (next > 1000000000LL) break;
                k = next;
            }
            values.push_back(clampK(k + rnd.next(-2, 2)));
        }
    } else {
        t = rnd.next(10, 60);
        for (int i = 0; i < t; ++i) {
            values.push_back(rnd.next(1, 1000000000));
        }
    }

    if (rnd.next(0, 4) == 0) {
        shuffle(values.begin(), values.end());
    }

    println(static_cast<int>(values.size()));
    for (int k : values) {
        println(k);
    }

    return 0;
}
