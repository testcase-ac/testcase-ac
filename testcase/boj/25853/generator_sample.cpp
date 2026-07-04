#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxS = 1000000000000000000LL;
    const long long maxDelta = 1000000LL;

    int mode = rnd.next(0, 5);
    long long delta;
    long long s;

    if (mode == 0) {
        delta = rnd.next(100LL, 250LL);
        s = rnd.next(2LL, 1000LL);
    } else if (mode == 1) {
        delta = rnd.next(100LL, 1000LL);
        s = rnd.next(2LL, 1000000LL);
    } else if (mode == 2) {
        delta = rnd.next(100LL, 5000LL);
        long long base = rnd.next(2LL, 1000000000LL);
        long long step = rnd.any(vector<long long>{2LL, 3LL, 5LL, 6LL, 30LL});
        s = max(2LL, base - base % step);
    } else if (mode == 3) {
        delta = rnd.next(10000LL, 100000LL);
        s = rnd.next(2LL, 1000000000000LL);
    } else if (mode == 4) {
        delta = rnd.next(100LL, maxDelta);
        s = rnd.next(maxS - 1000000000000LL, maxS);
    } else {
        delta = rnd.any(vector<long long>{100LL, 101LL, 999LL, 1000LL, 999999LL, maxDelta});
        s = rnd.next(2LL, maxS);
    }

    if (s > maxS) s = maxS;

    long long e = s + delta;
    long long length = delta + 1;
    long long maxK = 9LL * length / 10LL;

    vector<int> kModes = {0, 1, 2, 3};
    int kMode = rnd.any(kModes);
    long long k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = maxK;
    } else if (kMode == 2) {
        k = rnd.next(1LL, min(maxK, 20LL));
    } else {
        k = rnd.next(1LL, maxK);
    }

    println(s, e, k);
    return 0;
}
