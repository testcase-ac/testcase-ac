#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIMIT = 1000000000;
    vector<int> candidates = {
        1,
        2,
        3,
        4,
        7,
        8,
        15,
        16,
        31,
        32,
        63,
        64,
        LIMIT
    };

    int mode = rnd.next(0, 5);
    int n = 1;

    if (mode == 0) {
        int bit = rnd.next(0, 29);
        n = 1 << bit;
    } else if (mode == 1) {
        int bit = rnd.next(1, 29);
        int base = 1 << bit;
        int delta = rnd.next(-3, 3);
        n = base + delta;
    } else if (mode == 2) {
        int width = rnd.next(1, 29);
        n = (1 << width) - 1;
        if (rnd.next(0, 1) == 1 && n < LIMIT) {
            n++;
        }
    } else if (mode == 3) {
        n = rnd.next(1, 2000);
    } else if (mode == 4) {
        n = rnd.next(1, LIMIT);
    } else {
        n = rnd.any(candidates);
    }

    n = max(1, min(LIMIT, n));
    println(n);

    return 0;
}
