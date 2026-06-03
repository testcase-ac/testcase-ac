#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000LL;

    long long x = 0;
    long long y = 0;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        x = rnd.any(vector<long long>{0, 1, 9, 10, 11, MAX_VALUE});
        y = rnd.any(vector<long long>{0, 1, 9, 10, 11, MAX_VALUE});
    } else if (mode == 1) {
        long long base = rnd.next(0LL, 100000000LL) * 10LL;
        x = min(MAX_VALUE, base + rnd.next(0, 9));
        y = min(MAX_VALUE, base + rnd.next(0, 9));
    } else if (mode == 2) {
        x = rnd.next(0LL, 200LL);
        y = rnd.next(0LL, MAX_VALUE);
        if (rnd.next(0, 1)) swap(x, y);
    } else if (mode == 3) {
        x = rnd.next(0LL, 1000000LL);
        y = rnd.next(0LL, 1000000LL);
    } else if (mode == 4) {
        long long qx = rnd.next(0LL, 100000000LL);
        long long qy = rnd.next(0LL, 100000000LL);
        x = min(MAX_VALUE, qx * 10LL + rnd.next(8, 9));
        y = min(MAX_VALUE, qy * 10LL + rnd.next(0, 1));
    } else if (mode == 5) {
        long long small = rnd.next(0LL, 1000LL);
        long long large = rnd.next(MAX_VALUE - 1000LL, MAX_VALUE);
        x = small;
        y = large;
        if (rnd.next(0, 1)) swap(x, y);
    } else {
        x = rnd.next(0LL, MAX_VALUE);
        y = rnd.next(0LL, MAX_VALUE);
    }

    println(x, y);
    return 0;
}
