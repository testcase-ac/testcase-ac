#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(1, 100);
        m = n;
    } else if (mode == 2) {
        n = rnd.next(1, 100);
        m = rnd.next(1, 3);
        if (rnd.next(0, 1)) {
            int tmp = n;
            n = m;
            m = tmp;
        }
    } else if (mode == 3) {
        n = rnd.next(95, 100);
        m = rnd.next(95, 100);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        m = rnd.next(80, 100);
        if (rnd.next(0, 1)) {
            int tmp = n;
            n = m;
            m = tmp;
        }
    } else {
        n = rnd.next(1, 100);
        m = rnd.next(1, 100);
    }

    println(n, m);
    return 0;
}
