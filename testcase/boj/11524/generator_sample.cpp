#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxYear = 281474976710656LL;
    const long long period = 3750000000LL;

    int p = rnd.next(4, 25);
    vector<long long> years;
    years.reserve(p);

    int mode = rnd.next(0, 5);
    for (int i = 0; i < p; ++i) {
        long long y;
        if (mode == 0) {
            y = rnd.next(1, 100);
        } else if (mode == 1) {
            long long center = 1LL << rnd.next(0, 48);
            long long delta = rnd.next(-5, 5);
            y = max(1LL, min(maxYear, center + delta));
        } else if (mode == 2) {
            long long center = rnd.next(1LL, maxYear);
            long long delta = rnd.next(-1000, 1000);
            y = max(1LL, min(maxYear, center + delta));
        } else if (mode == 3) {
            long long block = rnd.next(0LL, maxYear / period);
            long long delta = rnd.next(-8, 8);
            y = max(1LL, min(maxYear, block * period + delta));
        } else if (mode == 4) {
            y = maxYear - rnd.next(0LL, 1000LL);
        } else {
            y = rnd.wnext(maxYear, -3) + 1;
        }
        years.push_back(y);
    }

    if (rnd.next(0, 2) == 0) {
        years[rnd.next(0, p - 1)] = 1;
    }
    if (rnd.next(0, 2) == 0) {
        years[rnd.next(0, p - 1)] = maxYear;
    }

    println(p);
    int baseK = rnd.next(1, 1000000000 - p + 1);
    for (int i = 0; i < p; ++i) {
        int k = rnd.next(0, 3) == 0 ? rnd.next(1, 1000000000) : baseK + i;
        println(k, years[i]);
    }

    return 0;
}
