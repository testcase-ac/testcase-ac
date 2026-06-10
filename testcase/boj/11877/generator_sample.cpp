#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

static int64 maxCapacity(int64 n) {
    if (n <= 2) return 0;
    return (n - 1) * (n - 2) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int64 maxX = 1000000000000000LL;
    int mode = rnd.next(0, 8);
    int64 n;
    int64 x;

    if (mode == 0) {
        n = rnd.next(1, 2);
        x = rnd.next(1LL, 20LL);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        x = rnd.next(1LL, maxCapacity(n));
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        x = maxCapacity(n) + rnd.next(1LL, 20LL);
    } else if (mode == 3) {
        n = rnd.next(3, 100);
        vector<int64> choices = {1, maxCapacity(n), maxCapacity(n) - 1};
        x = rnd.any(choices);
    } else if (mode == 4) {
        n = rnd.next(100, 5000);
        x = rnd.next(1LL, min<int64>(maxCapacity(n), 1000000LL));
    } else if (mode == 5) {
        n = rnd.next(1000, 1000000);
        x = rnd.next(1LL, min<int64>(maxCapacity(n), maxX));
    } else if (mode == 6) {
        n = rnd.next(3, 1000000);
        x = min(maxX, maxCapacity(n) + rnd.next(1LL, 1000000LL));
    } else if (mode == 7) {
        n = rnd.next(100000, 1000000);
        x = maxX - rnd.next(0LL, 1000000LL);
    } else {
        n = rnd.next(3, 1000000);
        x = rnd.next(1LL, maxX);
    }

    x = max<int64>(1, min<int64>(x, maxX));
    println(n, x);

    return 0;
}
