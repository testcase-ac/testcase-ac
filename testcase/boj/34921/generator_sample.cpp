#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = 0;
    int t = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int ages[] = {0, 1, 25, 31, 100};
        int tiers[] = {0, 1, 15, 16, 31};
        a = ages[rnd.next(0, 4)];
        t = tiers[rnd.next(0, 4)];
    } else if (mode == 1) {
        t = rnd.next(0, 31);
        a = 35 + t + rnd.next(-2, 2);
        a = std::max(0, std::min(100, a));
    } else if (mode == 2) {
        t = rnd.next(0, 31);
        a = 25 + t + rnd.next(-2, 2);
        a = std::max(0, std::min(100, a));
    } else if (mode == 3) {
        a = rnd.next(0, 30);
        t = rnd.next(20, 31);
    } else if (mode == 4) {
        a = rnd.next(60, 100);
        t = rnd.next(0, 10);
    } else {
        a = rnd.next(0, 100);
        t = rnd.next(0, 31);
    }

    println(a, t);
    return 0;
}
