#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(3, 8);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(3, 40);
        k = rnd.next(0, 1) == 0 ? 1 : n;
    } else if (mode == 2) {
        n = rnd.next(3, 40);
        int mid = (n + 1) / 2;
        int radius = rnd.next(0, 2);
        k = rnd.next(std::max(1, mid - radius), std::min(n, mid + radius));
    } else if (mode == 3) {
        n = rnd.next(30, 40);
        k = rnd.next(1, n);
    } else if (mode == 4) {
        n = 40;
        k = rnd.next(1, n);
    } else {
        n = rnd.next(3, 40);
        int offset = rnd.next(0, std::min(4, n - 1));
        k = rnd.next(0, 1) == 0 ? 1 + offset : n - offset;
    }

    println(n);
    println(k);

    return 0;
}
