#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 100000000000LL;
    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        14LL,
        15LL,
        16LL,
        62LL,
        63LL,
        64LL,
        254LL,
        255LL,
        256LL,
        1022LL,
        1023LL,
        1024LL,
        2023LL,
        1234567895LL,
        maxN
    };

    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.next(1LL, 300LL);
    } else if (mode == 1) {
        long long anchor = rnd.any(anchors);
        long long delta = rnd.next(-8LL, 8LL);
        n = min(maxN, max(1LL, anchor + delta));
    } else if (mode == 2) {
        long long base = rnd.any(vector<long long>{3LL, 15LL, 63LL, 255LL, 1023LL});
        long long quotient = rnd.next(1LL, 2500LL);
        long long delta = rnd.next(-3LL, 3LL);
        n = base * quotient + delta;
        n = min(maxN, max(1LL, n));
    } else if (mode == 3) {
        long long block = rnd.next(1LL, maxN / 255LL);
        long long delta = rnd.next(0LL, 254LL);
        n = block * 255LL + delta;
        n = min(maxN, max(1LL, n));
    } else if (mode == 4) {
        long long block = rnd.next(1LL, maxN / 1023LL);
        long long delta = rnd.next(-5LL, 5LL);
        n = block * 1023LL + delta;
        n = min(maxN, max(1LL, n));
    } else {
        n = rnd.next(maxN - 1000000LL, maxN);
    }

    println(n);
    return 0;
}
