#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_VALUE = 1;
    const long long MAX_VALUE = 1000000000000LL;

    vector<long long> anchors = {
        MIN_VALUE,
        2,
        9,
        10,
        999,
        1000,
        999999999999LL,
        MAX_VALUE
    };

    int mode = rnd.next(6);
    long long a, b, c;

    if (mode == 0) {
        a = rnd.next(MIN_VALUE, 1000LL);
        b = rnd.next(MIN_VALUE, 1000LL);
        c = rnd.next(MIN_VALUE, 1000LL);
    } else if (mode == 1) {
        a = rnd.next(MAX_VALUE - 1000, MAX_VALUE);
        b = rnd.next(MAX_VALUE - 1000, MAX_VALUE);
        c = rnd.next(MAX_VALUE - 1000, MAX_VALUE);
    } else if (mode == 2) {
        a = rnd.any(anchors);
        b = rnd.any(anchors);
        c = rnd.any(anchors);
    } else if (mode == 3) {
        long long x = rnd.next(MIN_VALUE, MAX_VALUE);
        a = x;
        b = x;
        c = x;
    } else if (mode == 4) {
        a = rnd.next(MIN_VALUE, 1000000LL);
        b = rnd.next(1000000LL, 1000000000LL);
        c = rnd.next(1000000000LL, MAX_VALUE);
    } else {
        a = rnd.next(MIN_VALUE, MAX_VALUE);
        b = rnd.next(MIN_VALUE, MAX_VALUE);
        c = rnd.next(MIN_VALUE, MAX_VALUE);
    }

    println(a, b, c);
    return 0;
}
