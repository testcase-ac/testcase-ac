#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int k;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1, 12);
        k = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        k = rnd.next(1000, 5000);
    } else if (mode == 2) {
        n = rnd.next(1000, 5000);
        k = rnd.next(1, 20);
    } else if (mode == 3) {
        n = rnd.next(4500, 5000);
        k = rnd.next(4500, 5000);
    } else if (mode == 4) {
        int edge[] = {1, 2, 4999, 5000};
        n = edge[rnd.next(0, 3)];
        k = rnd.next(1, 5000);
    } else {
        n = rnd.next(1, 5000);
        k = rnd.next(1, 5000);
    }

    println(n, k);
    return 0;
}
