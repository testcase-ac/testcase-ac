#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

using int64 = long long;

const int64 LIMIT = 10000000000000000LL;

int64 randomSmall() {
    return rnd.next(1LL, 50LL);
}

int64 randomLarge() {
    return rnd.next(LIMIT - 2000, LIMIT);
}

pair<int64, int64> makeRange(int mode) {
    if (mode == 0) {
        int64 x = randomSmall();
        int64 m = rnd.next(1LL, 12LL);
        return {x, m};
    }

    if (mode == 1) {
        int64 x = rnd.next(1LL, 40LL);
        int64 len = rnd.next(1LL, 20LL);
        int64 end = x + len - 1;
        end += (3 - end % 4 + 4) % 4;
        return {x, max(1LL, end - x + 1)};
    }

    if (mode == 2) {
        int64 x = randomLarge();
        int64 maxM = LIMIT - x + 1;
        int64 m = rnd.next(1LL, min<int64>(maxM, 200LL));
        return {x, m};
    }

    if (mode == 3) {
        int64 x = rnd.next(1LL, 1000LL);
        int64 m = rnd.next(1LL, 1000LL);
        return {x, m};
    }

    int64 x = rnd.next(1LL, LIMIT);
    int64 m = rnd.next(1LL, min<int64>(LIMIT, 1000000LL));
    return {x, m};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 40 : 12);
    vector<pair<int64, int64>> quarries;

    if (mode == 4) {
        int pairs = rnd.next(1, 8);
        for (int i = 0; i < pairs; ++i) {
            auto range = makeRange(rnd.next(0, 4));
            quarries.push_back(range);
            quarries.push_back(range);
        }
        if (rnd.next(0, 1) == 1) {
            quarries.push_back(makeRange(rnd.next(0, 4)));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int rangeMode = mode;
            if (mode == 5) {
                rangeMode = rnd.next(0, 4);
            }
            quarries.push_back(makeRange(rangeMode));
        }
    }

    shuffle(quarries.begin(), quarries.end());

    println((int)quarries.size());
    for (auto [x, m] : quarries) {
        println(x, m);
    }

    return 0;
}
