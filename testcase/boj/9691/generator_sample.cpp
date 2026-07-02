#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        int bit = rnd.next(0, 29);
        n = 1 << bit;
    } else if (mode == 2) {
        int bit = rnd.next(1, 29);
        int base = 1 << bit;
        int delta = rnd.next(-5, 5);
        n = max(1, min(maxN, base + delta));
    } else if (mode == 3) {
        int bit = rnd.next(2, 29);
        int lo = 1 << (bit - 1);
        int hi = min(maxN, (1 << bit) - 1);
        n = rnd.next(lo, hi);
    } else if (mode == 4) {
        n = maxN - rnd.next(0, 1000);
    } else if (mode == 5) {
        vector<int> edges = {1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 17,
                             31, 32, 33, 1023, 1024, 1025, maxN};
        n = rnd.any(edges);
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
