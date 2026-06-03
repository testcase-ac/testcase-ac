#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        m = n;
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        m = rnd.next(std::max(1, n - 3), n);
    } else if (mode == 4) {
        n = rnd.next(15, 20);
        m = rnd.next(1, n);
    } else {
        n = rnd.next(1, 20);
        m = rnd.next(1, n);
    }

    println(n, m);
    return 0;
}
