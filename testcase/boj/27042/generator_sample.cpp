#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 7100000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        int k = rnd.next(0, 22);
        n = 1 << k;
    } else if (mode == 2) {
        int k = rnd.next(1, 22);
        int base = 1 << k;
        int delta = rnd.next(-3, 3);
        n = base + delta;
        n = max(1, min(maxN, n));
    } else if (mode == 3) {
        n = rnd.next(1000, 100000);
    } else if (mode == 4) {
        n = rnd.next(maxN - 1000, maxN);
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
