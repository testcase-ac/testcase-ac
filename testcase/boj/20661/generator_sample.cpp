#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int LIM = 10000000;

pair<int, int> intervalAround(int center, int radius) {
    int lo = max(1, center - rnd.next(0, radius));
    int hi = min(LIM, center + rnd.next(0, radius));
    if (lo > hi) swap(lo, hi);
    return {lo, hi};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    vector<vector<int>> cases;

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int a, b, c, d;

        if (mode == 0) {
            int len = rnd.next(1, 8);
            a = rnd.next(1, LIM - len + 1);
            b = a + len - 1;
            c = a;
            d = b;
        } else if (mode == 1) {
            int len = rnd.next(1, 7);
            a = rnd.next(1, LIM - len + 1);
            b = a + len - 1;
            c = max(1, a - rnd.next(0, 5));
            d = min(LIM, b + rnd.next(0, 5));
        } else if (mode == 2) {
            a = rnd.next(1, 40);
            b = rnd.next(a, min(LIM, a + rnd.next(0, 8)));
            c = rnd.next(1, 40);
            d = rnd.next(c, min(LIM, c + rnd.next(0, 8)));
        } else if (mode == 3) {
            int base = rnd.next(LIM - 200, LIM);
            auto left = intervalAround(base, 20);
            auto right = intervalAround(rnd.next(LIM - 200, LIM), 20);
            a = left.first;
            b = left.second;
            c = right.first;
            d = right.second;
        } else if (mode == 4) {
            a = rnd.next(1, 25);
            b = rnd.next(a, min(LIM, a + rnd.next(3, 12)));
            c = rnd.next(1, 25);
            d = rnd.next(c, min(LIM, c + rnd.next(3, 12)));
        } else {
            a = rnd.next(1, LIM);
            b = min(LIM, a + rnd.next(0, 3));
            int gap = rnd.next(1, 10);
            c = min(LIM, b + gap);
            d = min(LIM, c + rnd.next(0, 5));
            if (c > d) c = d;
        }

        cases.push_back({a, b, c, d});
    }

    println(t);
    for (const auto& row : cases) println(row);

    return 0;
}
