#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int s = 1;
    int m = 1;

    if (mode <= 1) {
        s = (mode == 0 ? rnd.next(1, 32) : rnd.next(900, 1023));
        m = rnd.next(1, 1023);
    } else if (mode <= 3) {
        int need = rnd.next(1, 1023);
        int extra = rnd.next(0, 1023 ^ need);
        m = need | extra;
        s = 1023 + need;
    } else if (mode == 4) {
        int need = rnd.next(1, 1023);
        int missing = 1 << rnd.next(0, 9);
        need |= missing;
        m = rnd.next(1, 1023) & ~missing;
        s = 1023 + need;
    } else {
        s = 2048;
        m = rnd.next(1, 1023);
    }

    println(s, m);
    return 0;
}
