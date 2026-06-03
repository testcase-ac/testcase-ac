#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;

    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = 100;
    } else if (mode == 2) {
        k = rnd.next(2, 9);
    } else if (mode == 3) {
        k = rnd.next(2, 20) * 5;
    } else if (mode == 4) {
        k = rnd.next(10, 50);
    } else {
        k = rnd.next(1, 100);
    }

    println(k);
    return 0;
}
