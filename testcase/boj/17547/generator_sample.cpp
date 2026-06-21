#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 40);
    } else if (mode == 1) {
        n = 2 + 4 * rnd.next(0, (maxN - 2) / 4);
    } else if (mode == 2) {
        n = 1 + 2 * rnd.next(0, (maxN - 1) / 2);
    } else if (mode == 3) {
        n = 4 * rnd.next(1, maxN / 4);
    } else if (mode == 4) {
        int m = rnd.next(1, 31623);
        int k = rnd.next(0, m - 1);
        n = m * m - k * k;
    } else if (mode == 5) {
        n = maxN - rnd.next(0, 40);
    } else {
        std::vector<int> edges = {1, 2, 3, 4, 7, 10, 15, 999999998, 999999999, maxN};
        n = rnd.any(edges);
    }

    println(n);
    return 0;
}
