#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000000000LL;
    long long a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(1LL, 1000LL);
    } else if (mode == 1) {
        long long side = rnd.next(1LL, 1000000000LL);
        a = side * side;
    } else if (mode == 2) {
        long long side = rnd.next(2LL, 1000000000LL);
        long long square = side * side;
        long long lowDelta = -min(1000LL, square - 1);
        long long highDelta = min(1000LL, LIMIT - square);
        a = square + rnd.next(lowDelta, highDelta);
    } else if (mode == 3) {
        long long high = rnd.next(1000000000000LL, LIMIT);
        a = high;
    } else {
        long long side = rnd.next(999999000LL, 1000000000LL);
        long long square = side * side;
        long long lowDelta = -min(1000000LL, square - 1);
        long long highDelta = min(1000000LL, LIMIT - square);
        a = square + rnd.next(lowDelta, highDelta);
    }

    println(a);
    return 0;
}
