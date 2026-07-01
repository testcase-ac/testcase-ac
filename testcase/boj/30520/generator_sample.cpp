#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 10);
    } else if (mode == 2) {
        n = rnd.next(11, 100);
    } else if (mode == 3) {
        n = rnd.next(101, 500);
    } else if (mode == 4) {
        n = rnd.next(501, 999);
    } else {
        n = 1000;
    }

    println(n, 1);
    return 0;
}
