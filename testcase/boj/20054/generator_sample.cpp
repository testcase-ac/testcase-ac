#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 3500;
    const int maxK = 12;

    int mode = rnd.next(0, 6);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, maxK);
    } else if (mode == 1) {
        k = rnd.next(1, maxK);
        n = min(maxN, (1 << k) - 1);
    } else if (mode == 2) {
        k = rnd.next(1, maxK);
        int capacity = min(maxN, (1 << k) - 1);
        n = min(maxN, capacity + rnd.next(1, 5));
    } else if (mode == 3) {
        k = rnd.next(1, maxK);
        n = rnd.next(max(1, maxN - 30), maxN);
    } else if (mode == 4) {
        k = rnd.next(1, 4);
        n = rnd.next(1, min(maxN, 40));
    } else if (mode == 5) {
        k = rnd.next(8, maxK);
        n = rnd.next(1, maxN);
    } else {
        n = rnd.next(1, maxN);
        k = rnd.next(1, maxK);
    }

    println(n, k);
    return 0;
}
