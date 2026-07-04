#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int k;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = rnd.next(1, 5);
        k = rnd.next(0, 2 * n);
    } else if (mode == 1) {
        n = rnd.next(45, 50);
        k = rnd.next(0, 2 * n);
    } else if (mode == 2) {
        n = rnd.next(1, 50);
        k = rnd.any(std::vector<int>{0, 1, std::max(0, 2 * n - 1), 2 * n});
    } else if (mode == 3) {
        n = rnd.next(1, 50);
        int delta = rnd.next(-3, 3);
        k = std::clamp(n + delta, 0, 2 * n);
    } else if (mode == 4) {
        n = rnd.next(1, 50);
        int half = rnd.next(0, n);
        k = 2 * half;
    } else {
        n = rnd.next(1, 50);
        k = rnd.next(0, 2 * n);
        if (k % 2 == 0 && k < 2 * n) {
            ++k;
        } else if (k % 2 == 0) {
            --k;
        }
    }

    println(n, k);
    return 0;
}
