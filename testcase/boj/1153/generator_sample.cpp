#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 7);
    } else if (mode == 1) {
        n = rnd.next(8, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 10000);
    } else if (mode == 4) {
        n = rnd.next(1, maxN / 2) * 2;
    } else {
        n = maxN - rnd.next(0, 1000);
    }

    if (rnd.next(0, 3) == 0) {
        vector<int> edges = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 999983, 999999, maxN};
        n = rnd.any(edges);
    }

    n = max(1, min(maxN, n));
    println(n);

    return 0;
}
