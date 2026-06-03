#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(9980, 10000);
    } else if (mode == 2) {
        int block = rnd.next(0, 2000);
        int offset = rnd.next(0, 4);
        n = block * 5 + offset + 1;
        if (n > 10000) n = 10000;
    } else if (mode == 3) {
        int block = rnd.next(1, 2000);
        n = block * 5;
    } else {
        n = rnd.next(1, 10000);
    }

    println(n);
    return 0;
}
