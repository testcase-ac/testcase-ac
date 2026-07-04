#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000000LL;

    vector<long long> anchors = {
        1LL,
        2LL,
        4LL,
        5LL,
        9LL,
        10LL,
        14LL,
        24LL,
        25LL,
        49LL,
        50LL,
        99LL,
        100LL,
        999LL,
        1000LL,
        1000000LL,
        1000000000LL,
        1000000000000LL,
        999999999999999937LL,
        maxN
    };

    long long n;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        long long base = rnd.next(0LL, 20000000000000000LL) * 50LL;
        long long offset = rnd.next(0LL, 49LL);
        n = min(maxN, max(1LL, base + offset));
    } else if (mode == 2) {
        long long anchor = rnd.any(anchors);
        long long delta = rnd.next(-60LL, 60LL);
        n = min(maxN, max(1LL, anchor + delta));
    } else if (mode == 3) {
        long long q = rnd.next(0LL, 10000000000000000LL);
        long long rem = rnd.any(vector<long long>{0LL, 1LL, 4LL, 5LL, 9LL, 10LL, 24LL, 25LL, 49LL});
        n = min(maxN, max(1LL, q * 100LL + rem));
    } else if (mode == 4) {
        n = rnd.next(maxN - 1000000LL, maxN);
    } else {
        n = rnd.next(1LL, maxN);
    }

    println(n);
    return 0;
}
