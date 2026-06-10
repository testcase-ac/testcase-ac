#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 3;
    } else if (mode == 1) {
        n = rnd.next(4, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 5000);
    } else if (mode == 4) {
        n = rnd.next(5001, 50000);
    } else if (mode == 5) {
        n = rnd.next(199900, 200000);
    } else {
        n = rnd.next(3, 200000);
    }

    println(n);
    return 0;
}
