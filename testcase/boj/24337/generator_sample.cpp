#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n;
    int a;
    int b;

    if (mode == 0) {
        n = 1;
        a = 1;
        b = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        a = 1;
        b = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        a = rnd.next(1, n);
        b = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 25);
        int sum = rnd.next(2, n + 1);
        a = rnd.next(1, sum - 1);
        b = sum - a;
    } else if (mode == 4) {
        n = rnd.next(2, 25);
        int sum = rnd.next(n + 2, 2 * n);
        a = rnd.next(sum - n, n);
        b = sum - a;
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        a = rnd.next(1, n);
        b = a;
    } else if (mode == 6) {
        n = rnd.next(90, 160);
        a = rnd.next(1, n);
        b = rnd.next(1, n);
    } else if (mode == 7) {
        n = 100000;
        a = rnd.next(1, n);
        b = rnd.next(1, n);
    } else {
        n = rnd.next(2, 40);
        a = rnd.next(1, n);
        b = rnd.next(1, n);
    }

    println(n, a, b);
    return 0;
}
