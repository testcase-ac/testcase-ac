#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 15);
    } else if (mode == 3) {
        n = rnd.next(16, 40);
    } else if (mode == 4) {
        n = rnd.next(80, 100);
    } else {
        n = rnd.any(std::vector<int>{1, 2, 3, 99, 100});
    }

    int k;
    if (mode == 0) {
        k = rnd.next(1, 3);
    } else if (mode == 5) {
        k = rnd.any(std::vector<int>{1, 3});
    } else {
        k = rnd.next(1, 3);
    }

    println(n, k);
    return 0;
}
