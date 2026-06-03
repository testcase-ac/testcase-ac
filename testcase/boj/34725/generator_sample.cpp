#include "testlib.h"

int evenInRange(int lo, int hi) {
    int first = (lo % 2 == 0) ? lo : lo + 1;
    int last = (hi % 2 == 0) ? hi : hi - 1;
    return first + 2 * rnd.next((last - first) / 2 + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 2;
    int m = 2;

    if (mode == 0) {
        n = 2;
        m = evenInRange(2, 30);
    } else if (mode == 1) {
        n = evenInRange(2, 30);
        m = 2;
    } else if (mode == 2) {
        n = evenInRange(4, 40);
        m = n;
    } else if (mode == 3) {
        n = evenInRange(4, 40);
        m = evenInRange(4, 40);
    } else if (mode == 4) {
        n = evenInRange(900, 1000);
        m = evenInRange(2, 40);
    } else {
        n = evenInRange(2, 40);
        m = evenInRange(900, 1000);
    }

    if (rnd.next(2) == 1) {
        int tmp = n;
        n = m;
        m = tmp;
    }

    println(n, m);
    return 0;
}
