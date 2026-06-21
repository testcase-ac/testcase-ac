#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using int64 = long long;

int64 pickA(int mode) {
    if (mode == 0) {
        return rnd.next(1, 200);
    }
    if (mode == 1) {
        return rnd.next(900000LL, 1000000LL);
    }
    if (mode == 2) {
        return rnd.next(999999000000LL, 1000000000000LL);
    }
    return rnd.next(1LL, 1000000000000LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(1, 8);
    vector<pair<pair<int64, int64>, int64>> cases;

    for (int i = 0; i < c; ++i) {
        int mode = rnd.next(0, 3);
        int64 a = pickA(mode);
        int64 maxWidth = min<int64>(1000000LL, 1000000000000LL - a);

        int64 width;
        if (mode == 0) {
            width = rnd.next(0LL, min<int64>(60LL, maxWidth));
        } else if (mode == 1) {
            width = rnd.next(0LL, min<int64>(1000LL, maxWidth));
        } else if (mode == 2) {
            width = rnd.next(0LL, min<int64>(1000LL, maxWidth));
        } else {
            width = rnd.next(0LL, min<int64>(200LL, maxWidth));
        }

        int64 b = a + width;
        if (b < 2) {
            b = 2;
        }
        int64 p;
        int pMode = rnd.next(0, 4);
        if (pMode == 0) {
            p = 2;
        } else if (pMode == 1) {
            p = min<int64>(b, rnd.next(2LL, min<int64>(30LL, b)));
        } else if (pMode == 2) {
            p = max<int64>(2LL, b - rnd.next(0LL, min<int64>(10LL, b - 2)));
        } else if (pMode == 3 && b >= a) {
            p = rnd.next(2LL, b);
        } else {
            p = b;
        }

        cases.push_back({{a, b}, p});
    }

    println(cases.size());
    for (const auto& tc : cases) {
        println(tc.first.first, tc.first.second, tc.second);
    }

    return 0;
}
