#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr long long kMaxValue = 100000000000000LL;

    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        4LL,
        8LL,
        16LL,
        31LL,
        32LL,
        63LL,
        64LL,
        99LL,
        100LL,
        999LL,
        1000LL,
        999999LL,
        1000000LL,
        99999999999999LL,
        kMaxValue,
    };

    long long s = 1;
    long long t = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        s = rnd.any(anchors);
        t = s;
    } else if (mode == 1) {
        s = rnd.any(anchors);
        long long width = rnd.next(0LL, 40LL);
        if (s > kMaxValue - width) {
            s = kMaxValue - width;
        }
        t = s + width;
    } else if (mode == 2) {
        t = rnd.any(anchors);
        s = rnd.next(1LL, t);
    } else if (mode == 3) {
        s = rnd.next(1LL, 2000000LL);
        t = rnd.next(s, min(kMaxValue, s + rnd.next(0LL, 2000000LL)));
    } else if (mode == 4) {
        long long offset = rnd.next(0LL, 2000000LL);
        t = kMaxValue - offset;
        long long width = rnd.next(0LL, 2000000LL);
        s = max(1LL, t - width);
    } else {
        s = rnd.next(1LL, kMaxValue);
        long long room = kMaxValue - s;
        long long width = rnd.next(0LL, min(room, 1000000000LL));
        t = s + width;
    }

    println(s, t);
    return 0;
}
