#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k;
    int n;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = rnd.next(0, 8);
        k = rnd.next(0, n);
    } else if (mode == 1) {
        n = rnd.next(1, 63);
        k = rnd.next(0, 1);
    } else if (mode == 2) {
        n = rnd.next(0, 63);
        k = n;
    } else if (mode == 3) {
        n = rnd.next(50, 63);
        k = rnd.next(0, n);
    } else if (mode == 4) {
        n = rnd.next(2, 63);
        k = rnd.next(n / 2, n);
    } else if (mode == 5) {
        n = rnd.next(0, 63);
        k = rnd.next(0, n);
        if ((k + n) % 2 == 1 && k < n) {
            ++k;
        }
    } else {
        n = rnd.next(0, 63);
        k = rnd.next(0, n);
    }

    println(k, n);
    return 0;
}
