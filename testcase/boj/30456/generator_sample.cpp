#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int l;

    if (mode == 0) {
        n = 0;
        l = rnd.next(2, 18);
    } else if (mode == 1) {
        n = rnd.next(1, 9);
        l = rnd.next(2, 18);
    } else if (mode == 2) {
        n = rnd.next(0, 9);
        l = 2;
    } else if (mode == 3) {
        n = rnd.next(0, 9);
        l = 18;
    } else if (mode == 4) {
        n = rnd.next(0, 9);
        l = rnd.next(2, 5);
    } else {
        n = rnd.next(0, 9);
        l = rnd.next(14, 18);
    }

    println(n, l);
    return 0;
}
