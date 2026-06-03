#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_VALUE = 1LL;
    const long long MAX_VALUE = 1000000000000LL;
    const long long MAX_WIDTH = 1000000LL;

    long long minValue = 1;
    long long width = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        minValue = rnd.next(1LL, 200LL);
        width = rnd.next(0LL, 200LL);
    } else if (mode == 1) {
        minValue = rnd.next(1LL, MAX_VALUE);
        width = 0;
    } else if (mode == 2) {
        long long root = rnd.next(2LL, 1000000LL);
        long long square = root * root;
        long long radius = rnd.next(0LL, 500LL);
        minValue = max(MIN_VALUE, square - radius);
        width = rnd.next(0LL, min(MAX_WIDTH, radius * 2 + 100LL));
    } else if (mode == 3) {
        minValue = rnd.next(1LL, MAX_VALUE - MAX_WIDTH);
        width = rnd.next(1LL, MAX_WIDTH);
    } else if (mode == 4) {
        minValue = rnd.next(MAX_VALUE - MAX_WIDTH, MAX_VALUE);
        width = rnd.next(0LL, MAX_VALUE - minValue);
    } else {
        long long span = rnd.next(1LL, 10000LL);
        minValue = rnd.next(1LL, MAX_VALUE - span);
        width = rnd.next(0LL, span);
    }

    long long maxValue = min(MAX_VALUE, minValue + width);
    println(minValue, maxValue);
    return 0;
}
