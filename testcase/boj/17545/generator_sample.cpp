#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(1, 5);
        k = rnd.next(80, 100);
    } else if (mode == 2) {
        n = rnd.next(80, 100);
        k = rnd.next(1, 5);
    } else if (mode == 3) {
        n = rnd.next(80, 100);
        k = rnd.next(80, 100);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        k = rnd.next(2, 12);
    } else if (mode == 5) {
        n = rnd.next(20, 60);
        k = rnd.next(20, 60);
    } else if (mode == 6) {
        n = rnd.next(1, 100);
        k = rnd.next(1, 100);
    } else {
        n = rnd.any(std::vector<int>{1, 2, 6, 8, 10, 50, 99, 100});
        k = rnd.any(std::vector<int>{1, 2, 3, 9, 10, 50, 99, 100});
    }

    println(n, k);
    return 0;
}
