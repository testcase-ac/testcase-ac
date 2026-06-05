#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampN(int n) {
    return max(1, min(100000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        12, 16, 20, 24, 30, 36, 48, 60, 72,
        99, 100, 119, 120, 143, 144, 209, 210,
        999, 1000, 1596, 2583, 4180, 6764,
        9999, 10000, 32767, 32768, 49999,
        65535, 65536, 99991, 99999, 100000
    };
    vector<int> nPlusOneAnchors = {
        2, 3, 4, 5, 6, 7, 8, 10, 12, 13,
        16, 18, 21, 25, 31, 32, 34, 55, 89,
        144, 233, 377, 610, 987, 1597, 2584,
        4181, 6765, 10946, 17711, 28657, 46368,
        75025, 99991, 100001
    };

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        int base = rnd.any(anchors);
        n = clampN(base + rnd.next(-3, 3));
    } else if (mode == 2) {
        int value = rnd.any(nPlusOneAnchors);
        n = clampN(value - 1 + rnd.next(-2, 2));
    } else if (mode == 3) {
        int factor = rnd.any(vector<int>{2, 3, 5, 8, 13, 21, 34, 55, 89, 144});
        int multiple = rnd.next(1, 100001 / factor);
        n = clampN(factor * multiple - 1);
    } else if (mode == 4) {
        n = rnd.next(90000, 100000);
    } else {
        n = rnd.next(1, 100000);
    }

    println(n);
    return 0;
}
