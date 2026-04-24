#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: select among size categories
    int mode = rnd.next(0, 3);
    int N;
    if (mode == 0) {
        // tiny cases: easy to hand-check
        N = rnd.next(1, 20);
    } else if (mode == 1) {
        // small cases
        N = rnd.next(21, 1000);
    } else if (mode == 2) {
        // medium cases
        N = rnd.next(1001, 100000);
    } else {
        // large cases
        if (rnd.next(0, 4) == 0) {
            // exact upper bound occasionally
            N = 1000000;
        } else {
            N = rnd.next(900000, 1000000);
        }
    }

    // Occasionally pick special values: powers of two or one less
    if (rnd.next() < 0.2) {
        vector<int> specials;
        for (int k = 0; k <= 20; ++k) {
            int p = (1 << k);
            if (p >= 1 && p <= 1000000) specials.push_back(p);
            int pm1 = p - 1;
            if (pm1 >= 1 && pm1 <= 1000000) specials.push_back(pm1);
        }
        specials.push_back(999999);
        specials.push_back(1000000);
        N = rnd.any(specials);
    }

    // Ensure within bounds
    N = max(1, min(N, 1000000));

    // Output single test case
    println(N);

    return 0;
}
