#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxValue = 4294967295LL;
    const vector<long long> pivots = {
        0LL, 1LL, 9LL, 10LL, 11LL, 99LL, 100LL, 101LL, 999LL, 1000LL, 1001LL,
        9999LL, 10000LL, 10001LL, 99999LL, 100000LL, 100001LL,
        999999LL, 1000000LL, 1000001LL, 999999999LL, 1000000000LL,
        1000000001LL, maxValue - 1, maxValue
    };

    int cases = rnd.next(8, 18);
    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 5);
        long long m = 0;
        long long n = 0;

        if (mode == 0) {
            m = rnd.any(pivots);
            n = m;
        } else if (mode == 1) {
            m = rnd.next(0LL, 10000LL);
            n = min(maxValue, m + rnd.next(0LL, 250LL));
        } else if (mode == 2) {
            long long center = rnd.any(pivots);
            long long left = rnd.next(0LL, 50LL);
            long long right = rnd.next(0LL, 50LL);
            m = max(0LL, center - left);
            n = min(maxValue, center + right);
        } else if (mode == 3) {
            m = 0;
            n = rnd.any(pivots);
        } else if (mode == 4) {
            m = rnd.next(maxValue - 1000000LL, maxValue);
            n = rnd.next(m, maxValue);
        } else {
            m = rnd.next(0LL, maxValue);
            long long width = rnd.next(0LL, 1000000LL);
            n = min(maxValue, m + width);
        }

        println(m, n);
    }

    println(-1, -1);
    return 0;
}
