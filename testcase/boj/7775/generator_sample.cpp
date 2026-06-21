#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n, p, k, d;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, n);
        d = 1;
        p = rnd.next(0, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = rnd.next(2, n);
        d = rnd.next(2, k);
        int minDistinctSum = d * (d - 1) / 2;
        p = minDistinctSum;
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        k = rnd.next(2, n);
        d = rnd.next(2, k);
        int minDistinctSum = d * (d - 1) / 2;
        p = rnd.next(0, minDistinctSum > 0 ? minDistinctSum - 1 : 0);
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        k = rnd.next(2, n - 1);
        d = 1;
        int topScore = rnd.next(1, 20);
        p = k * topScore + rnd.next(0, (n - k) * topScore);
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        k = n;
        d = rnd.next(1, k);
        p = rnd.next(0, 100);
    } else if (mode == 5) {
        n = rnd.next(900, 1000);
        k = rnd.next(1, n);
        d = rnd.next(1, k);
        p = rnd.next(0, 1000000);
    } else if (mode == 6) {
        n = rnd.next(1, 20);
        k = rnd.next(1, n);
        d = rnd.next(1, k);
        p = 1000000;
    } else {
        n = rnd.next(1, 30);
        k = rnd.next(1, n);
        d = rnd.next(1, k);
        p = rnd.next(0, 200);
    }

    println(n, p, k, d);
    return 0;
}
