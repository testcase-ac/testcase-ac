#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(1, min(77777, x));
}

int nearSquareValue() {
    int root = rnd.next(1, 278);
    int offset = rnd.next(-3, 3);
    return clampValue(root * root + offset);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 1;
    int m = 1;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = rnd.next(1, 20);
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(1, 77777);
        m = rnd.next(1, 5);
        if (rnd.next(0, 1)) swap(n, m);
    } else if (mode == 2) {
        n = nearSquareValue();
        m = nearSquareValue();
    } else if (mode == 3) {
        int base = rnd.next(1, 77777);
        int delta = rnd.next(-100, 100);
        n = clampValue(base);
        m = clampValue(base + delta);
    } else if (mode == 4) {
        n = rnd.next(70000, 77777);
        m = rnd.next(1, 77777);
        if (rnd.next(0, 1)) swap(n, m);
    } else {
        vector<int> interesting = {1, 2, 3, 4, 8, 9, 10, 16, 25, 36, 49,
                                   64, 81, 100, 121, 144, 256, 625, 1024,
                                   4096, 10000, 40000, 77777};
        n = rnd.any(interesting);
        m = rnd.any(interesting);
    }

    println(n, m);
    return 0;
}
