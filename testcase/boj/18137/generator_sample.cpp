#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxK = 2401;
    int mode = rnd.next(0, 6);
    int k = 0;

    if (mode == 0) {
        k = rnd.next(0, 5);
    } else if (mode == 1) {
        k = rnd.next(6, 80);
    } else if (mode == 2) {
        k = rnd.next(81, 140);
    } else if (mode == 3) {
        k = rnd.next(141, 600);
    } else if (mode == 4) {
        k = rnd.next(601, 1800);
    } else if (mode == 5) {
        k = rnd.next(1801, maxK);
    } else {
        int edge[] = {0, 1, 2, 99, 100, 101, maxK - 2, maxK - 1, maxK};
        k = edge[rnd.next(0, 8)];
    }

    println(k);
    return 0;
}
