#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampN(int n) {
    return max(1, min(100000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        int k = rnd.next(2, 450);
        int tri = k * (k + 1) / 2;
        n = clampN(tri + rnd.next(-2, 2));
    } else if (mode == 2) {
        int k = rnd.next(2, 220);
        int add = rnd.next(0, 200);
        int splitSum = k * (k + 1) / 2 + k * add;
        n = clampN(splitSum + rnd.next(-1, 1));
    } else if (mode == 3) {
        n = rnd.next(21, 1000);
    } else if (mode == 4) {
        n = rnd.next(1000, 100000);
    } else {
        n = clampN(100000 - rnd.wnext(1000, 3));
    }

    println(n);
    return 0;
}
