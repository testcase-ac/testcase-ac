#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 50);
        k = rnd.next(1, 200);
    } else if (mode == 2) {
        n = rnd.next(900000, 1000000);
        k = rnd.next(1, 20);
    } else if (mode == 3) {
        n = rnd.next(1, 20);
        k = rnd.next(450000, 500000);
    } else if (mode == 4) {
        n = rnd.next(950000, 1000000);
        k = rnd.next(450000, 500000);
    } else {
        n = rnd.next(1, 1000000);
        k = rnd.next(1, 500000);
    }

    if (rnd.next(0, 9) == 0) n = rnd.any(std::vector<int>{1, 2, 999999, 1000000});
    if (rnd.next(0, 9) == 0) k = rnd.any(std::vector<int>{1, 2, 499999, 500000});

    println(n, k);
    return 0;
}
