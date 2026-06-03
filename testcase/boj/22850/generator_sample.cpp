#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(int x) {
    return max(1, min(100000, x));
}

int around(int center, int radius) {
    return clampValue(center + rnd.next(-radius, radius));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 1;
    int m = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        vector<int> edges = {1, 2, 3, 4, 5, 34, 35, 36, 100000};
        n = rnd.any(edges);
        m = rnd.any(edges);
    } else if (mode == 2) {
        int base = rnd.next(1, 18) * 34;
        n = around(base, 4);
        m = around(base + rnd.next(-34, 34), 4);
    } else if (mode == 3) {
        n = around(100000, rnd.next(0, 120));
        m = rnd.next(1, 100000);
    } else if (mode == 4) {
        n = rnd.next(1, 100000);
        m = n;
    } else {
        n = rnd.next(1, 100000);
        m = rnd.next(1, 100000);
    }

    if (rnd.next(2)) swap(n, m);

    println(n, m);
    return 0;
}
