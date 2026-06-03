#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int m;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            n = 2;
            m = rnd.next(2, 40);
        } else {
            n = rnd.next(2, 40);
            m = 2;
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        m = n;
    } else if (mode == 3) {
        n = rnd.next(195, 200);
        m = rnd.next(2, 20);
        if (rnd.next(0, 1) == 0) {
            int tmp = n;
            n = m;
            m = tmp;
        }
    } else if (mode == 4) {
        n = rnd.next(190, 200);
        m = rnd.next(190, 200);
    } else {
        n = rnd.next(2, 200);
        m = rnd.next(2, 200);
    }

    println(n, m);
    return 0;
}
