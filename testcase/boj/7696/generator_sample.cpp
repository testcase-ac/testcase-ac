#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;

    int mode = rnd.next(0, 4);
    int targetCount = rnd.next(4, 18);

    if (mode == 0) {
        values = {1, 2, 9, 10, 11, 25};
    } else if (mode == 1) {
        values = {9998, 9999, 10000, 10001, 10002};
    } else if (mode == 2) {
        values = {999990, 999995, 999999, 1000000};
    } else if (mode == 3) {
        int start = rnd.next(1, 1000000 - targetCount + 1);
        for (int i = 0; i < targetCount; ++i) {
            values.push_back(start + i);
        }
    } else {
        int lo = rnd.next(1, 900000);
        int hi = rnd.next(lo, 1000000);
        while ((int)values.size() < targetCount) {
            values.push_back(rnd.next(lo, hi));
        }
    }

    while ((int)values.size() < targetCount) {
        int band = rnd.next(0, 5);
        if (band == 0) {
            values.push_back(rnd.next(1, 30));
        } else if (band == 1) {
            values.push_back(rnd.next(31, 1000));
        } else if (band == 2) {
            values.push_back(rnd.next(9000, 11000));
        } else if (band == 3) {
            values.push_back(rnd.next(100001, 999999));
        } else {
            values.push_back(rnd.next(999900, 1000000));
        }
    }

    shuffle(values.begin(), values.end());

    for (int n : values) {
        println(n);
    }
    println(0);

    return 0;
}
