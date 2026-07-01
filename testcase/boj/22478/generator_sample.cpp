#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

const int64 MIN_S = 1;
const int64 MAX_S = 1000000000000000000LL;

int64 clampS(int64 value) {
    return max(MIN_S, min(MAX_S, value));
}

int64 withJitter(int64 anchor, int64 radius) {
    return clampS(anchor + rnd.next(-radius, radius));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int64> powers;
    for (int64 value = 1; value <= MAX_S / 10; value *= 10) {
        powers.push_back(value);
    }
    powers.push_back(MAX_S);

    int mode = rnd.next(0, 6);
    int64 s;
    if (mode == 0) {
        s = rnd.next(MIN_S, 250LL);
    } else if (mode == 1) {
        int64 anchor = rnd.any(powers);
        s = withJitter(anchor, 250);
    } else if (mode == 2) {
        int64 block = rnd.next(0LL, MAX_S / 15);
        int64 offset = rnd.next(-30LL, 30LL);
        s = clampS(block * 15 + offset);
    } else if (mode == 3) {
        int64 base = rnd.next(1LL, 1000000LL);
        int64 scale = rnd.any(powers);
        if (scale > MAX_S / base) {
            scale = MAX_S / base;
        }
        s = withJitter(base * scale, 1000);
    } else if (mode == 4) {
        s = rnd.next(MAX_S - 1000000LL, MAX_S);
    } else {
        s = rnd.next(MIN_S, MAX_S);
    }

    println(s);
    return 0;
}
