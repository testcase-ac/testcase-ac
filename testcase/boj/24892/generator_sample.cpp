#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int a;
    int b;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = 2;
        int width = rnd.next(1, 8);
        a = rnd.next(0, 1000 - width);
        b = a + width;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int width = rnd.next(1, 20);
        a = rnd.next(0, 1000 - width);
        b = a + width;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        a = 0;
        b = rnd.next(1, 1000);
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        b = 1000;
        a = rnd.next(0, 999);
    } else if (mode == 4) {
        n = rnd.next(50, 200);
        int width = rnd.next(1, 1000);
        a = rnd.next(0, 1000 - width);
        b = a + width;
    } else if (mode == 5) {
        n = rnd.next(900, 1000);
        int width = rnd.next(1, 80);
        a = rnd.next(0, 1000 - width);
        b = a + width;
    } else if (mode == 6) {
        n = rnd.next(2, 1000);
        int width = rnd.next(900, 1000);
        a = rnd.next(0, 1000 - width);
        b = a + width;
    } else {
        n = rnd.next(2, 1000);
        a = rnd.next(0, 999);
        b = rnd.next(a + 1, 1000);
    }

    println(n);
    println(a, b);

    return 0;
}
