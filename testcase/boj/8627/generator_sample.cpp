#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

long long pickCoord(long long center, long long radius) {
    long long lo = max(-1000000000LL, center - radius);
    long long hi = min(1000000000LL, center + radius);
    return rnd.next(lo, hi);
}

Point pickNear(long long centerX, long long centerY, long long radius) {
    return {pickCoord(centerX, radius), pickCoord(centerY, radius)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    int p;
    long long s;
    vector<Point> stones;

    if (mode == 0) {
        n = rnd.next(1, 3);
        p = rnd.next(1, n);
        s = rnd.next(1LL, 10LL);
        for (int i = 0; i < n; ++i) {
            stones.push_back(pickNear(0, 0, 5));
        }
    } else if (mode == 1) {
        n = rnd.next(5, 14);
        p = rnd.next(1, n);
        s = rnd.next(2LL, 8LL);
        long long x = rnd.next(-20LL, 20LL);
        long long y = rnd.next(-20LL, 20LL);
        stones.push_back({x, y});
        for (int i = 1; i < n; ++i) {
            x += rnd.next(1LL, max(1LL, s));
            y += rnd.next(-1LL, 1LL);
            stones.push_back({x, y});
        }
    } else if (mode == 2) {
        n = rnd.next(8, 20);
        p = rnd.next(1, n);
        s = rnd.next(3LL, 15LL);
        long long radius = max(1LL, s / 2);
        for (int i = 0; i < n; ++i) {
            stones.push_back(pickNear(0, 0, radius));
        }
    } else if (mode == 3) {
        n = rnd.next(8, 24);
        p = rnd.next(1, n);
        s = rnd.next(2LL, 12LL);
        int leftCount = rnd.next(3, n - 3);
        for (int i = 0; i < leftCount; ++i) {
            stones.push_back(pickNear(-30, 0, s / 2 + 1));
        }
        for (int i = leftCount; i < n; ++i) {
            stones.push_back(pickNear(30, 0, s / 2 + 1));
        }
    } else {
        n = rnd.next(6, 16);
        p = rnd.next(1, n);
        s = rnd.any(vector<long long>{1LL, 2LL, 1000000000LL});
        vector<Point> anchors = {
            {-1000000000LL, -1000000000LL},
            {-1000000000LL, 1000000000LL},
            {1000000000LL, -1000000000LL},
            {1000000000LL, 1000000000LL},
            {0, 0},
        };
        for (int i = 0; i < n; ++i) {
            Point anchor = rnd.any(anchors);
            long long radius = (s == 1000000000LL ? 3LL : s);
            stones.push_back(pickNear(anchor.first, anchor.second, radius));
        }
    }

    if (rnd.next(2) == 0) {
        shuffle(stones.begin(), stones.end());
    }

    println(n, p, s);
    for (const auto& stone : stones) {
        println(stone.first, stone.second);
    }

    return 0;
}
