#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h = rnd.next(0, 23);
    int m = rnd.next(0, 59);
    int s = rnd.next(0, 59);

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        s = 59;
    } else if (mode == 1) {
        m = 59;
        s = rnd.next(58, 59);
    } else if (mode == 2) {
        h = 23;
        m = 59;
        s = rnd.next(58, 59);
    } else if (mode == 3) {
        h = 0;
        m = rnd.next(0, 1);
        s = rnd.next(0, 1);
    } else if (mode == 4) {
        h = rnd.next(0, 23);
        m = 0;
        s = 0;
    }

    println(h, m, s);
    return 0;
}
