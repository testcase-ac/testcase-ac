#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int a = rnd.next(1, 100);
    int d = rnd.next(1, 100);
    int k = rnd.next(1, 100);

    if (mode == 0) {
        d = 100;
        k = rnd.next(1, 100);
    } else if (mode == 1) {
        d = rnd.next(1, 5);
        k = rnd.next(1, 5);
    } else if (mode == 2) {
        d = rnd.next(1, 10);
        k = rnd.next(50, 100);
    } else if (mode == 3) {
        d = rnd.next(80, 99);
        k = rnd.next(1, 20);
    } else if (mode == 4) {
        a = rnd.any(std::vector<int>{1, 100});
        d = rnd.next(1, 100);
        k = rnd.next(1, 100);
    } else if (mode == 5) {
        d = rnd.any(std::vector<int>{1, 2, 5, 10, 25, 50, 75, 99, 100});
        k = rnd.any(std::vector<int>{1, 2, 5, 10, 25, 50, 75, 99, 100});
    }

    println(a, d, k);
    return 0;
}
