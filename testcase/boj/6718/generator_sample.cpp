#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomEven(int lo, int hi) {
    if (lo % 2 != 0) ++lo;
    if (hi % 2 != 0) --hi;
    return 2 * rnd.next(lo / 2, hi / 2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 5);
    int queryCount = rnd.next(1, 20);

    if (mode == 0) {
        for (int i = 0; i < queryCount; ++i) {
            values.push_back(randomEven(4, 80));
        }
    } else if (mode == 1) {
        for (int i = 0; i < queryCount; ++i) {
            values.push_back(randomEven(32000, 32766));
        }
    } else if (mode == 2) {
        int step = 2 * rnd.next(1, 20);
        int start = randomEven(4, 32766 - step * (queryCount - 1));
        for (int i = 0; i < queryCount; ++i) {
            values.push_back(start + step * i);
        }
    } else if (mode == 3) {
        int base = randomEven(4, 400);
        for (int i = 0; i < queryCount; ++i) {
            values.push_back(min(32766, base * rnd.next(1, 80)));
            if (values.back() % 2 != 0) --values.back();
            values.back() = max(values.back(), 4);
        }
    } else {
        vector<int> anchors = {4, 6, 8, 10, 12, 14, 16, 18, 20,
                               100, 1024, 4096, 10000, 20000, 32760, 32766};
        shuffle(anchors.begin(), anchors.end());
        for (int i = 0; i < queryCount; ++i) {
            if (i < int(anchors.size()) && rnd.next(0, 1) == 0) {
                values.push_back(anchors[i]);
            } else {
                values.push_back(randomEven(4, 32766));
            }
        }
    }

    shuffle(values.begin(), values.end());
    for (int n : values) {
        println(n);
    }
    println(0);

    return 0;
}
