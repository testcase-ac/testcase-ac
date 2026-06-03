#include "testlib.h"

int clampPos(int v) {
    if (v < 0) return 0;
    if (v > 100) return 100;
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int a = 0, b = 0, x = 0, y = 0;

    if (mode == 0) {
        a = rnd.next(0, 100);
        b = a;
        x = rnd.next(0, 100);
        y = rnd.next(0, 100);
    } else if (mode == 1) {
        x = rnd.next(0, 100);
        y = x;
        a = rnd.next(0, 100);
        b = rnd.next(0, 100);
    } else if (mode == 2) {
        a = rnd.any(std::vector<int>{0, 100});
        b = 100 - a;
        x = rnd.next(0, 100);
        y = rnd.next(0, 100);
    } else if (mode == 3) {
        x = rnd.next(0, 20);
        y = rnd.next(80, 100);
        a = clampPos(x + rnd.next(-3, 3));
        b = clampPos(y + rnd.next(-3, 3));
    } else if (mode == 4) {
        x = rnd.next(80, 100);
        y = rnd.next(0, 20);
        a = clampPos(x + rnd.next(-3, 3));
        b = clampPos(y + rnd.next(-3, 3));
    } else if (mode == 5) {
        int center = rnd.next(20, 80);
        a = rnd.next(center - 10, center + 10);
        b = rnd.next(center - 10, center + 10);
        x = rnd.any(std::vector<int>{0, 100});
        y = 100 - x;
    } else if (mode == 6) {
        a = rnd.next(0, 15);
        b = rnd.next(85, 100);
        x = rnd.next(40, 60);
        y = rnd.next(40, 60);
    } else {
        a = rnd.next(0, 100);
        b = rnd.next(0, 100);
        x = rnd.next(0, 100);
        y = rnd.next(0, 100);
    }

    println(a, b, x, y);
    return 0;
}
