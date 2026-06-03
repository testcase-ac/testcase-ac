#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 100;
    } else if (mode == 2) {
        n = rnd.next(2, 10);
    } else if (mode == 3) {
        n = rnd.next(90, 99);
    } else {
        n = rnd.next(1, 100);
    }

    println(n);
    return 0;
}
