#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 300);
    } else if (mode == 3) {
        n = rnd.next(301, 2000);
    } else {
        n = rnd.next(4500, 5000);
    }

    println(n);
    return 0;
}
