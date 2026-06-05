#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int k;
    int p;
    int w;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        n = 1;
        k = 1;
        p = rnd.next(1, 20);
        w = rnd.next(1, p);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = 1;
        p = rnd.next(1, 2000);
        w = p;
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        k = n;
        p = rnd.next(2, 2000);
        w = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        k = rnd.next(1, n);
        w = rnd.next(1, 50);
        int q = rnd.next(1, 2000 / w);
        p = q * w;
    } else if (mode == 4) {
        n = rnd.next(2, 30);
        k = rnd.next(1, n);
        w = rnd.next(2, 100);
        int q = rnd.next(1, (2000 - 1) / w);
        p = q * w + rnd.next(1, w - 1);
    } else if (mode == 5) {
        n = rnd.next(50, 1000);
        k = rnd.any(std::vector<int>{1, n, (n + 1) / 2, rnd.next(1, n)});
        p = rnd.next(1000, 2000);
        w = rnd.next(1, p);
    } else if (mode == 6) {
        n = 1000;
        k = rnd.next(1, n);
        p = 2000;
        w = rnd.next(1, p);
    } else {
        n = rnd.next(1, 1000);
        k = rnd.next(1, n);
        p = rnd.next(1, 2000);
        w = rnd.next(1, p);
    }

    println(n, k, p, w);
    return 0;
}
