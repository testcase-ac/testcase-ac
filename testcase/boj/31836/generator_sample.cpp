#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 20);
    } else if (mode == 2) {
        int residue = rnd.next(0, 2);
        int k = rnd.next(1, 20);
        n = 3 * k + residue;
        if (n < 2) n += 3;
    } else if (mode == 3) {
        n = rnd.next(1900, 2000);
    } else if (mode == 4) {
        int residue = rnd.next(0, 2);
        int lo = 2 + (residue - 2 % 3 + 3) % 3;
        int hi = 2000 - (2000 - residue + 3) % 3;
        int count = (hi - lo) / 3 + 1;
        n = lo + 3 * rnd.next(0, count - 1);
    } else {
        n = rnd.next(2, 2000);
    }

    println(n);
    return 0;
}
