#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int64 LIMIT = 1000000000000000000LL;

    vector<int64> sums;
    for (int x = 0; x < 60; ++x) {
        for (int y = x; y < 60; ++y) {
            int64 value = (1LL << x) + (1LL << y);
            if (value <= LIMIT) {
                sums.push_back(value);
            }
        }
    }

    int n = rnd.next(1, 40);
    vector<int64> values;
    values.reserve(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 5);
        int64 m;

        if (mode == 0) {
            m = rnd.any(sums);
        } else if (mode == 1) {
            int64 base = rnd.any(sums);
            int64 delta = rnd.next(-20, 20);
            m = min(LIMIT, max(1LL, base + delta));
        } else if (mode == 2) {
            int64 base = 1LL << rnd.next(0, 59);
            int64 delta = rnd.next(-1000, 1000);
            m = min(LIMIT, max(1LL, base + delta));
        } else if (mode == 3) {
            m = rnd.next(1LL, 200LL);
        } else if (mode == 4) {
            m = LIMIT - rnd.next(0LL, 1000000LL);
        } else {
            m = rnd.next(1LL, LIMIT);
        }

        values.push_back(m);
    }

    shuffle(values.begin(), values.end());

    println(n);
    for (int64 m : values) {
        println(m);
    }

    return 0;
}
