#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

long long jitter(long long radius) {
    return rnd.next(-radius, radius);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        long long halfSide = rnd.next(1, 40);
        long long noise = rnd.next(0, 5);
        points = {{halfSide, halfSide}, {-halfSide, halfSide}, {-halfSide, -halfSide}, {halfSide, -halfSide}};
        for (auto& p : points) {
            p.first += jitter(noise);
            p.second += jitter(noise);
        }
    } else if (mode == 1) {
        long long baseX = rnd.next(-25, 25);
        long long baseY = rnd.next(-25, 25);
        long long spread = rnd.next(0, 12);
        for (int i = 0; i < 4; ++i) {
            points.push_back({baseX + jitter(spread), baseY + jitter(spread)});
        }
    } else if (mode == 2) {
        long long span = rnd.next(1, 80);
        points = {{rnd.next(-span, span), 0},
                  {0, rnd.next(-span, span)},
                  {rnd.next(-span, span), 0},
                  {0, rnd.next(-span, span)}};
    } else if (mode == 3) {
        long long lim = rnd.next(1000000LL, 400000000LL);
        points = {{-lim, -lim}, {lim, -lim}, {-lim, lim}, {lim, lim}};
        int edits = rnd.next(0, 3);
        for (int i = 0; i < edits; ++i) {
            int idx = rnd.next(0, 3);
            points[idx].first = rnd.next(-lim, lim);
            points[idx].second = rnd.next(-lim, lim);
        }
    } else {
        long long lim = rnd.next(1, 100);
        for (int i = 0; i < 4; ++i) {
            points.push_back({rnd.next(-lim, lim), rnd.next(-lim, lim)});
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(points.begin(), points.end());
    }

    for (const auto& p : points) {
        println(p.first, p.second);
    }

    return 0;
}
