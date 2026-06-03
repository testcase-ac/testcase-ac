#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(3, 6);
        k = rnd.next(0, n * (n - 1) / 2);
    } else if (mode == 1) {
        n = rnd.next(3, 30);
        k = 0;
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        k = n * (n - 1) / 2;
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        int a = rnd.next(0, n);
        int b = rnd.next(0, n - a);
        int c = n - a - b;
        k = a * (b + c) + b * c;
    } else if (mode == 4) {
        n = rnd.next(20, 30);
        int limit = n * (n - 1) / 2;
        k = rnd.next(std::max(0, limit - 20), limit);
    } else if (mode == 5) {
        n = rnd.next(3, 30);
        int limit = n * (n - 1) / 2;
        k = rnd.next(0, std::min(limit, 40));
    } else {
        n = rnd.next(3, 30);
        int limit = n * (n - 1) / 2;
        k = rnd.next(0, limit);
    }

    println(n, k);
    return 0;
}
