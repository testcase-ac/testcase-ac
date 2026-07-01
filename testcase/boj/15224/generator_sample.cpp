#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMax = 1000000000000000000LL;

    int mode = rnd.next(0, 7);
    long long l = 1;
    long long r = 1;

    if (mode == 0) {
        l = rnd.next(1LL, 200LL);
        r = l + rnd.next(0LL, 30LL);
    } else if (mode == 1) {
        l = rnd.next(1LL, 1000000LL);
        r = l;
    } else if (mode == 2) {
        int exponent = rnd.next(0, 59);
        long long center = 1LL << exponent;
        long long offset = rnd.next(-20LL, 20LL);
        l = max(1LL, center + offset);
        r = l + rnd.next(0LL, 40LL);
    } else if (mode == 3) {
        int exponent = rnd.next(1, 59);
        long long center = (1LL << exponent) - 1;
        long long offset = rnd.next(-20LL, 20LL);
        l = max(1LL, center + offset);
        r = l + rnd.next(0LL, 40LL);
    } else if (mode == 4) {
        int exponent = rnd.next(1, 59);
        long long center = (1LL << exponent) + 1;
        long long offset = rnd.next(-20LL, 20LL);
        l = max(1LL, center + offset);
        r = l + rnd.next(0LL, 40LL);
    } else if (mode == 5) {
        long long width = rnd.next(0LL, 100LL);
        l = rnd.next(kMax - 1000000LL, kMax - width);
        r = l + width;
    } else if (mode == 6) {
        long long base = rnd.next(1LL, 1000000000000LL);
        long long width = rnd.next(0LL, 200LL);
        l = base * rnd.next(1LL, 1000000LL);
        if (l > kMax - width) l = kMax - width;
        r = l + width;
    } else {
        vector<long long> anchors = {1LL, 2LL, 3LL, 7LL, 8LL, 15LL, 16LL, 31LL, 32LL,
                                     63LL, 64LL, 127LL, 128LL, kMax};
        l = rnd.any(anchors);
        long long back = rnd.next(0LL, min(25LL, l - 1));
        long long forward = rnd.next(0LL, min(25LL, kMax - l));
        l -= back;
        r = l + back + forward;
    }

    if (r > kMax) r = kMax;
    if (l > r) l = r;

    println(l, r);
    return 0;
}
