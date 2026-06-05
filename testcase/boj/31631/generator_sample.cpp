#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 1000);
    } else if (mode == 4) {
        n = rnd.next(1001, 4999);
    } else {
        n = 5000;
    }

    println(n);
    return 0;
}
