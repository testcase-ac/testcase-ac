#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int k;
    int mode = rnd.next(8);

    if (mode == 0) {
        n = rnd.next(2, 8);
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        k = rnd.next(1, 3);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = n;
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        k = rnd.next(n, 1000);
    } else if (mode == 4) {
        n = rnd.next(900, 1000);
        k = rnd.next(1, 20);
    } else if (mode == 5) {
        n = rnd.next(900, 1000);
        k = rnd.next(900, 1000);
    } else if (mode == 6) {
        n = rnd.next(2, 1000);
        k = rnd.next(1, 1000);
    } else {
        n = rnd.any(std::vector<int>{2, 3, 10, 999, 1000});
        k = rnd.any(std::vector<int>{1, 2, 10, 999, 1000});
    }

    println(n, k);
    return 0;
}
