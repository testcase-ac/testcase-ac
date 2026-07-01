#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int a = 0;
    int b = 0;

    if (mode == 0) {
        a = rnd.next(0, 1);
        b = 1 - a;
    } else if (mode == 1) {
        a = rnd.next(1, 40);
    } else if (mode == 2) {
        b = rnd.next(1, 40);
    } else if (mode == 3) {
        a = rnd.next(1, 40);
        b = rnd.next(1, 40);
    } else if (mode == 4) {
        a = 0;
        b = 2 * rnd.next(1, 25);
    } else if (mode == 5) {
        a = rnd.next(1, 25);
        b = 2 * rnd.next(0, 25) + 1;
    } else if (mode == 6) {
        int total = rnd.next(2, 80);
        a = rnd.next(0, total);
        b = total - a;
    } else if (mode == 7) {
        int total = rnd.next(99950, 100000);
        a = rnd.next(0, total);
        b = total - a;
    } else {
        a = rnd.next(0, 100000);
        b = rnd.next(0, 100000 - a);
        if (a + b == 0) {
            if (rnd.next(0, 1) == 0) {
                a = 1;
            } else {
                b = 1;
            }
        }
    }

    println(a, b);
    return 0;
}
