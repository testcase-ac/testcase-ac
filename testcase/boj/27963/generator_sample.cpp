#include "testlib.h"
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int d1 = 1, d2 = 2, chi = 50;

    if (mode == 0) {
        d1 = rnd.next(1, 98);
        d2 = d1 + 1;
        chi = rnd.next(1, 99);
    } else if (mode == 1) {
        d1 = rnd.next(1, 5);
        d2 = rnd.next(95, 99);
        chi = rnd.next(1, 99);
    } else if (mode == 2) {
        d1 = rnd.next(1, 99);
        do {
            d2 = rnd.next(1, 99);
        } while (d1 == d2);
        chi = rnd.any(std::vector<int>{1, 2, 5, 95, 98, 99});
    } else if (mode == 3) {
        d1 = rnd.next(1, 99);
        do {
            d2 = rnd.next(1, 99);
        } while (d1 == d2);
        chi = rnd.next(45, 55);
    } else {
        d1 = rnd.next(1, 99);
        do {
            d2 = rnd.next(1, 99);
        } while (d1 == d2);
        chi = rnd.next(1, 99);
    }

    if (rnd.next(0, 1)) std::swap(d1, d2);
    println(d1, d2, chi);

    return 0;
}
