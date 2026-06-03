#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 50000;
    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 40);
    } else if (mode == 2) {
        n = rnd.next(41, 300);
    } else if (mode == 3) {
        n = rnd.next(301, 3000);
    } else if (mode == 4) {
        n = rnd.next(3001, maxN);
    } else if (mode == 5) {
        n = maxN - rnd.next(0, 200);
    } else {
        int block = rnd.next(0, 200);
        n = 3 * block + rnd.next(1, 3);
    }

    println(n);
    return 0;
}
