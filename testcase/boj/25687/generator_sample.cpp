#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(2, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 20);
    } else if (mode == 3) {
        n = rnd.next(21, 200);
    } else if (mode == 4) {
        n = rnd.next(1900, 2000);
    } else {
        n = 2000;
    }

    println(n);
    return 0;
}
