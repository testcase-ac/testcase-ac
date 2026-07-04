#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 20);
    } else if (mode == 3) {
        n = rnd.next(21, 60);
    } else if (mode == 4) {
        n = rnd.next(61, 99);
    } else {
        n = 100;
    }

    println(n);
    return 0;
}
