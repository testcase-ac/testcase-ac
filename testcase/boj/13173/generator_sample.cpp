#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = 1;
    int q = 0;
    int n = 1;
    int k = 0;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        p = rnd.next(1, 100);
        q = 0;
        n = rnd.next(1, 100);
        k = rnd.next(0, n);
    } else if (mode == 1) {
        p = rnd.next(1, 100);
        q = p;
        n = rnd.next(1, 100);
        k = rnd.next(0, n);
    } else if (mode == 2) {
        p = rnd.next(1, 100);
        q = rnd.next(0, p);
        n = rnd.next(1, 100);
        k = rnd.any(std::vector<int>{0, n});
    } else if (mode == 3) {
        p = rnd.next(1, 50) * 2;
        q = p / 2;
        n = rnd.next(2, 100);
        k = rnd.next(1, n - 1);
    } else if (mode == 4) {
        p = rnd.next(2, 100);
        q = rnd.next(1, p - 1);
        n = rnd.next(2, 20);
        k = rnd.next(1, n - 1);
    } else if (mode == 5) {
        p = rnd.next(2, 100);
        q = rnd.any(std::vector<int>{1, p - 1});
        n = rnd.next(2, 100);
        k = rnd.next(1, n - 1);
    } else if (mode == 6) {
        p = 100;
        q = rnd.next(0, 100);
        n = 100;
        k = rnd.next(0, 100);
    } else {
        p = rnd.next(1, 100);
        q = rnd.next(0, p);
        n = rnd.next(1, 100);
        k = rnd.next(0, n);
    }

    println(p);
    println(q);
    println(n);
    println(k);

    return 0;
}
