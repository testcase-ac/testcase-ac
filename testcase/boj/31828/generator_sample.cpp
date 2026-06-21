#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(4, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 500);
    } else if (mode == 3) {
        n = rnd.next(501, 5000);
    } else if (mode == 4) {
        n = rnd.next(5001, 99999);
    } else {
        n = rnd.next(99990, 100000);
    }

    println(n);
    return 0;
}
