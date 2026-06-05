#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 2000000;
    const vector<int> factorable = {
        1, 4, 12, 33, 88, 232, 609, 1596,
        4180, 10945, 28656, 75024, 196417, 514228, 1346268
    };

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        n = rnd.any(factorable);
    } else if (mode == 2) {
        int base = rnd.any(factorable);
        int delta = rnd.next(-5, 5);
        if (delta == 0) delta = rnd.next(0, 1) ? 1 : -1;
        n = max(1, min(maxN, base + delta));
    } else if (mode == 3) {
        n = rnd.next(maxN - 2000, maxN);
    } else if (mode == 4) {
        int limit = rnd.next(100, 50000);
        n = rnd.next(1, limit);
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
