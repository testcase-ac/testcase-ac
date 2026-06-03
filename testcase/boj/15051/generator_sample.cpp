#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a[3] = {0, 0, 0};
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int value = rnd.any(std::vector<int>{0, 1, 2, 10, 999, 1000});
        a[0] = a[1] = a[2] = value;
    } else if (mode == 1) {
        int floor = rnd.next(0, 2);
        a[floor] = rnd.next(0, 1000);
    } else if (mode == 2) {
        int zeroFloor = rnd.next(0, 2);
        for (int i = 0; i < 3; ++i) {
            if (i != zeroFloor) a[i] = rnd.next(0, 1000);
        }
    } else if (mode == 3) {
        int base = rnd.next(0, 20);
        int step = rnd.next(0, 490);
        a[0] = base;
        a[1] = std::min(1000, base + step);
        a[2] = std::min(1000, base + 2 * step);
    } else if (mode == 4) {
        int base = rnd.next(0, 20);
        int step = rnd.next(0, 490);
        a[2] = base;
        a[1] = std::min(1000, base + step);
        a[0] = std::min(1000, base + 2 * step);
    } else if (mode == 5) {
        for (int i = 0; i < 3; ++i) {
            a[i] = rnd.any(std::vector<int>{0, 1, 2, 10, 100, 999, 1000});
        }
    } else {
        int hi = rnd.any(std::vector<int>{5, 20, 100, 1000});
        for (int i = 0; i < 3; ++i) {
            a[i] = rnd.next(0, hi);
        }
    }

    for (int i = 0; i < 3; ++i) {
        println(a[i]);
    }

    return 0;
}
