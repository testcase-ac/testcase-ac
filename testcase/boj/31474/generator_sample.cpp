#include "testlib.h"

int evenInRange(int lo, int hi) {
    int count = (hi - lo) / 2 + 1;
    return lo + 2 * rnd.next(count);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = 28;
    } else if (mode == 2) {
        n = evenInRange(2, 10);
    } else if (mode == 3) {
        n = evenInRange(12, 20);
    } else {
        n = evenInRange(22, 28);
    }

    println(n);
    return 0;
}
