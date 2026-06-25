#include "testlib.h"
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 2000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(13, 200);
    } else if (mode == 2) {
        n = rnd.next(1000, 100000);
    } else if (mode == 3) {
        std::vector<int> bases = {31622, 46340, 1000000};
        int base = rnd.any(bases);
        n = base + rnd.next(-50, 50);
        n = std::max(1, std::min(maxN, n));
    } else if (mode == 4) {
        n = rnd.next(maxN - 1000, maxN);
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
