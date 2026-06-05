#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 1;
    int m = 1;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = 1;
        m = 1;
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(2, 30);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        m = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        m = n;
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    } else if (mode == 5) {
        n = rnd.next(2, 20);
        m = rnd.next(21, 80);
        if (rnd.next(0, 1)) {
            int tmp = n;
            n = m;
            m = tmp;
        }
    } else if (mode == 6) {
        n = rnd.next(900, 1000);
        m = rnd.next(1, 30);
        if (rnd.next(0, 1)) {
            int tmp = n;
            n = m;
            m = tmp;
        }
    } else {
        n = rnd.next(1, 1000);
        m = rnd.next(1, 1000);
    }

    println(n, m);
    return 0;
}
