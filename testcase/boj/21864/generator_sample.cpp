#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampN(int value) {
    return max(0, min(2000000, value));
}

int nearValue(int center, int radius) {
    return clampN(center + rnd.next(-radius, radius));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        0, 1, 2, 10, 42, 300300, 999999, 1000000, 1000001, 1999998, 1999999, 2000000
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = nearValue(rnd.any(anchors), rnd.next(1, 30));
    } else if (mode == 2) {
        int block = rnd.next(0, 2000);
        n = clampN(block * 1000 + rnd.next(-5, 5));
    } else if (mode == 3) {
        int power = 1;
        int exponent = rnd.next(0, 6);
        for (int i = 0; i < exponent; ++i) power *= 10;
        n = nearValue(power, rnd.next(0, 50));
    } else if (mode == 4) {
        n = rnd.next(0, 2000000);
    } else {
        n = rnd.next(1800000, 2000000);
    }

    println(n);
    return 0;
}
