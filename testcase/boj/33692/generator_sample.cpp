#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000000000LL;

int64 clampValue(int64 x) {
    return max<int64>(1, min<int64>(LIMIT, x));
}

pair<int64, int64> orderedPair(int64 a, int64 b) {
    a = clampValue(a);
    b = clampValue(b);
    if (a == b) {
        if (b < LIMIT) {
            ++b;
        } else {
            --a;
        }
    }
    if (a > b) swap(a, b);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int64 a, b;

    if (mode == 0) {
        a = rnd.next(1LL, 200LL);
        b = rnd.next(a + 1, 260LL);
    } else if (mode == 1) {
        int bit = rnd.next(1, 59);
        int64 pivot = 1LL << bit;
        int64 leftWidth = rnd.next(1LL, min<int64>(pivot - 1, 1000000LL));
        int64 rightWidth = rnd.next(0LL, min<int64>(pivot - 1, 1000000LL));
        a = pivot - leftWidth;
        b = pivot + rightWidth;
    } else if (mode == 2) {
        int bit = rnd.next(1, 59);
        int64 block = 1LL << bit;
        int64 base = rnd.next(0LL, (LIMIT - 1) / block) * block;
        int64 lo = base + rnd.next(0LL, block - 2);
        int64 maxHi = min<int64>(LIMIT, base + block - 1);
        a = max<int64>(1, lo);
        b = rnd.next(a + 1, maxHi);
    } else if (mode == 3) {
        int64 span = rnd.next(1LL, 1000000000000LL);
        a = rnd.next(1LL, LIMIT - span);
        b = a + span;
    } else if (mode == 4) {
        b = LIMIT - rnd.next(0LL, 1000000LL);
        a = b - rnd.next(1LL, 1000000LL);
    } else {
        a = rnd.next(1LL, LIMIT - 1);
        b = rnd.next(a + 1, LIMIT);
    }

    pair<int64, int64> input = orderedPair(a, b);
    println(input.first, input.second);
    return 0;
}
