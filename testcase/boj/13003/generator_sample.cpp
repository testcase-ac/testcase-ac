#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int l;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = rnd.next(1, 12);
        l = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 2000);
        l = rnd.next(1, 5);
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        l = rnd.next(1000, 2000);
    } else if (mode == 3) {
        int base = rnd.next(2, 44);
        n = base * base + rnd.next(-1, 1);
        if (n < 1) n = 1;
        if (n > 2000) n = 2000;
        l = rnd.next(2, 60);
    } else if (mode == 4) {
        n = rnd.next(1500, 2000);
        l = rnd.next(1500, 2000);
    } else if (mode == 5) {
        n = rnd.next(1, 3);
        l = rnd.next(1, 2000);
    } else {
        n = rnd.next(1, 2000);
        l = rnd.next(1, 2000);
    }

    println(n, l);
    return 0;
}
