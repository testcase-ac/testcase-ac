#include "testlib.h"
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 3 * n);
    } else if (mode == 1) {
        n = rnd.next(1, 100000);
        k = std::max(1, 2 * n - rnd.next(1, std::min(20, 2 * n - 1)));
    } else if (mode == 2) {
        n = rnd.next(1, 100000);
        k = 2 * n;
    } else if (mode == 3) {
        n = rnd.next(1, 100000);
        k = std::min(3 * n, 2 * n + rnd.next(1, std::min(20, n)));
    } else if (mode == 4) {
        n = rnd.next(1, 20);
        k = rnd.any(std::vector<int>{1, 3 * n});
    } else if (mode == 5) {
        n = rnd.next(99980, 100000);
        k = rnd.next(1, 3 * n);
    } else if (mode == 6) {
        n = 1;
        k = rnd.next(1, 3);
    } else {
        n = 100000;
        k = rnd.any(std::vector<int>{1, 199999, 200000, 200001, 300000});
    }

    println(n, k);
    return 0;
}
