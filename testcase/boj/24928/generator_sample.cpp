#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(26, 30);
    } else {
        n = rnd.next(1, 18);
    }

    long long limit = 1LL << n;
    long long value;
    switch (mode) {
        case 0:
            value = rnd.next(0, static_cast<int>(limit - 1));
            break;
        case 1:
            value = rnd.next(0, 63);
            break;
        case 2:
            value = limit - 1 - rnd.next(0, static_cast<int>(min(7LL, limit - 1)));
            break;
        case 3:
            value = 0;
            break;
        default:
            value = rnd.next(0, static_cast<int>(limit - 1));
            break;
    }

    long long maxD = limit - 1 - value;
    long long d;
    if (mode == 0 || mode == 4) {
        d = 0;
    } else if (mode == 2 || mode == 3) {
        d = maxD;
    } else if (maxD <= 20) {
        d = rnd.next(0, static_cast<int>(maxD));
    } else if (mode == 1) {
        d = rnd.next(static_cast<int>(maxD - min(100LL, maxD)), static_cast<int>(maxD));
    } else {
        d = rnd.next(0, static_cast<int>(maxD));
    }

    string s;
    for (int i = 0; i < n; ++i) {
        s += ((value >> i) & 1LL) ? 'B' : 'A';
    }

    println(s, d);
    return 0;
}
