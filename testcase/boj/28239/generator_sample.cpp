#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

static int64 makeValue(int x, int y) {
    return (1LL << x) + (1LL << y);
}

static pair<int, int> randomPair(int maxExp) {
    int x = rnd.next(0, maxExp);
    int y = rnd.next(x, maxExp);
    if (x == 59 && y == 59) {
        x = rnd.next(0, 58);
    }
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 4 ? 120 : 30);
    vector<int64> values;

    if (mode == 0) {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            int y = rnd.next(1, 8);
            int x = rnd.next(0, y);
            values.push_back(makeValue(x, y));
        }
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(0, 58);
            values.push_back(makeValue(x, x));
        }
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int y = rnd.next(54, 59);
            int x = (y == 59) ? rnd.next(0, 58) : rnd.next(0, y);
            values.push_back(makeValue(x, y));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int maxExp = rnd.next(0, 3) == 0 ? 12 : 59;
            auto [x, y] = randomPair(maxExp);
            values.push_back(makeValue(x, y));
        }
    }

    shuffle(values.begin(), values.end());

    println(static_cast<int>(values.size()));
    for (int64 value : values) {
        println(value);
    }

    return 0;
}
