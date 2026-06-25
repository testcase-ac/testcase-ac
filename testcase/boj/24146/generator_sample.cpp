#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int countFractions(int m) {
    int count = 0;
    for (int d = 2; d <= m; ++d) {
        for (int n = 1; n < d; ++n) {
            if (gcd(n, d) == 1) ++count;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int m;
    int k;

    if (mode == 0) {
        m = rnd.next(1, 4);
        int total = countFractions(m);
        k = rnd.next(1, min(200000, total + 2));
    } else if (mode == 1) {
        m = rnd.next(5, 12);
        int total = countFractions(m);
        k = rnd.next(1, min(200000, total + rnd.next(1, 8)));
    } else if (mode == 2) {
        m = rnd.next(13, 60);
        int total = countFractions(m);
        int lo = max(1, total - rnd.next(0, min(total - 1, 20)));
        int hi = min(200000, total + rnd.next(0, 20));
        k = rnd.next(lo, hi);
    } else if (mode == 3) {
        m = rnd.next(61, 300);
        k = rnd.next(1, min(200000, m * rnd.next(1, 20)));
    } else if (mode == 4) {
        m = rnd.next(301, 5000);
        k = rnd.next(1, 200000);
    } else if (mode == 5) {
        m = rnd.next(25000, 30000);
        k = rnd.next(1, 200000);
    } else {
        vector<pair<int, int>> boundaryCases = {
            {1, 1},
            {2, 1},
            {6, rnd.next(1, 14)},
            {30000, rnd.next(199000, 200000)},
        };
        auto chosen = rnd.any(boundaryCases);
        m = chosen.first;
        k = chosen.second;
    }

    println(m, k);
    return 0;
}
