#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(0, 10);
    } else if (mode == 1) {
        n = rnd.next(11, 200);
    } else if (mode == 2) {
        n = rnd.next(201, 5000);
    } else if (mode == 3) {
        n = rnd.next(12000, 21000);
    } else if (mode == 4) {
        n = rnd.next(50000, 90000);
    } else {
        n = rnd.next(90001, 100000);
    }

    println(n);
    return 0;
}
