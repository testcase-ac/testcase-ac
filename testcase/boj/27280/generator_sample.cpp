#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

long long smallOrLargeValue() {
    if (rnd.next(4) == 0) return rnd.next(900000000LL, 1000000000LL);
    return rnd.next(1, 40);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 5) {
        n = rnd.next(80, 220);
    } else if (rnd.next(5) == 0) {
        n = rnd.next(1, 3);
    } else {
        n = rnd.next(4, 18);
    }

    int m;
    if (rnd.next(4) == 0) {
        m = min(n, 10);
    } else if (rnd.next(3) == 0) {
        m = 1;
    } else {
        m = rnd.next(1, min(n, 10));
    }

    vector<pair<long long, long long>> soldiers;
    soldiers.reserve(n);

    if (mode == 0) {
        long long h = smallOrLargeValue();
        for (int i = 0; i < n; ++i) {
            soldiers.push_back({h, smallOrLargeValue()});
        }
    } else if (mode == 1) {
        long long h = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            h += rnd.next(0, 3);
            soldiers.push_back({h, smallOrLargeValue()});
        }
    } else if (mode == 2) {
        long long h = rnd.next(1, 20) + n * 3;
        for (int i = 0; i < n; ++i) {
            h -= rnd.next(0, 3);
            soldiers.push_back({max(1LL, h), smallOrLargeValue()});
        }
    } else if (mode == 3) {
        vector<long long> heights;
        int kinds = rnd.next(1, min(n, 5));
        for (int i = 0; i < kinds; ++i) {
            heights.push_back(smallOrLargeValue());
        }
        for (int i = 0; i < n; ++i) {
            soldiers.push_back({rnd.any(heights), smallOrLargeValue()});
        }
    } else if (mode == 4) {
        long long low = rnd.next(1, 20);
        long long high = rnd.next(21, 60);
        for (int i = 0; i < n; ++i) {
            long long h = (i % 2 == 0 ? low + rnd.next(0, 4) : high - rnd.next(0, 4));
            soldiers.push_back({h, smallOrLargeValue()});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            long long h = rnd.next(1LL, 1000000000LL);
            long long s = rnd.next(1LL, 1000000000LL);
            soldiers.push_back({h, s});
        }
    }

    println(n, m);
    for (auto [h, s] : soldiers) {
        println(h, s);
    }

    return 0;
}
