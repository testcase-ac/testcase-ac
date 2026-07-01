#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = 2;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        k = n - 1;
    } else if (mode == 3) {
        n = rnd.next(4, 30);
        k = rnd.next(2, n - 2);
    } else if (mode == 4) {
        n = rnd.next(31, 120);
        k = rnd.next(1, 8);
    } else if (mode == 5) {
        n = rnd.next(31, 120);
        k = rnd.next(n / 2, n - 1);
    } else if (mode == 6) {
        n = rnd.next(121, 500);
        k = rnd.next(1, n - 1);
    } else {
        n = rnd.any(std::vector<int>{999, 1000, 2999, 3000});
        k = rnd.any(std::vector<int>{1, 2, n / 2, n - 2, n - 1});
    }

    println(n, k);
    return 0;
}
