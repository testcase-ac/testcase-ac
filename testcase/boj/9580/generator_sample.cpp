#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    long long a = 0;
    long long b = 0;

    if (mode == 0) {
        n = rnd.next(1, 5);
        a = rnd.next(0, 5);
        b = rnd.next(0, 5);
    } else if (mode == 1) {
        n = 1;
        a = rnd.next(0, 20);
        b = rnd.next(0, 20);
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        a = 0;
        b = rnd.next(0, 100);
    } else if (mode == 3) {
        n = rnd.next(1, 12);
        a = rnd.next(0, 100);
        b = 0;
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        long long base = rnd.next(1, 1000);
        a = base + rnd.next(-5, 5);
        b = base + rnd.next(-5, 5);
    } else if (mode == 5) {
        n = rnd.next(2500, 3000);
        a = rnd.next(0, 4000);
        b = rnd.next(0, 4000);
    } else if (mode == 6) {
        n = rnd.next(1, 3000);
        a = rnd.next(999000000LL, 1000000000LL);
        b = rnd.next(0, 1000);
    } else {
        n = rnd.next(1, 3000);
        a = rnd.next(0, 1000);
        b = rnd.next(999000000LL, 1000000000LL);
    }

    println(n, a, b);
    return 0;
}
