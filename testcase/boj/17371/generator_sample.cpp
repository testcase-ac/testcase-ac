#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MIN_COORD = -10000;
const int MAX_COORD = 10000;

int coordNear(int center, int radius) {
    int lo = max(MIN_COORD, center - radius);
    int hi = min(MAX_COORD, center + radius);
    return rnd.next(lo, hi);
}

pair<int, int> randomPoint() {
    return {rnd.next(MIN_COORD, MAX_COORD), rnd.next(MIN_COORD, MAX_COORD)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> points;

    if (mode == 0) {
        int n = rnd.next(1, 12);
        pair<int, int> base = randomPoint();
        for (int i = 0; i < n; ++i) points.push_back(base);
    } else if (mode == 1) {
        int n = rnd.next(2, 18);
        bool vertical = rnd.next(0, 1);
        int fixed = rnd.next(MIN_COORD, MAX_COORD);
        for (int i = 0; i < n; ++i) {
            int variable = rnd.next(MIN_COORD, MAX_COORD);
            points.push_back(vertical ? make_pair(fixed, variable)
                                      : make_pair(variable, fixed));
        }
    } else if (mode == 2) {
        vector<pair<int, int>> corners = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
        };
        shuffle(corners.begin(), corners.end());

        int take = rnd.next(2, 4);
        for (int i = 0; i < take; ++i) points.push_back(corners[i]);

        int extra = rnd.next(0, 8);
        for (int i = 0; i < extra; ++i) {
            points.push_back({coordNear(0, 50), coordNear(0, 50)});
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 22);
        int cx = rnd.next(-9000, 9000);
        int cy = rnd.next(-9000, 9000);
        int radius = rnd.next(1, 200);

        for (int i = 0; i < n - 2; ++i) {
            points.push_back({coordNear(cx, radius), coordNear(cy, radius)});
        }
        points.push_back(randomPoint());
        points.push_back(randomPoint());
    } else if (mode == 4) {
        int n = rnd.next(3, 20);
        int x1 = rnd.next(-10000, 9990);
        int y1 = rnd.next(-10000, 9990);
        int x2 = rnd.next(x1 + 1, 10000);
        int y2 = rnd.next(y1 + 1, 10000);

        for (int i = 0; i < n; ++i) {
            int side = rnd.next(0, 3);
            if (side == 0) points.push_back({rnd.next(x1, x2), y1});
            if (side == 1) points.push_back({rnd.next(x1, x2), y2});
            if (side == 2) points.push_back({x1, rnd.next(y1, y2)});
            if (side == 3) points.push_back({x2, rnd.next(y1, y2)});
        }
    } else {
        int n = rnd.next(2, 30);
        int limit = rnd.any(vector<int>{10, 100, 1000, 10000});
        for (int i = 0; i < n; ++i) {
            points.push_back({rnd.next(-limit, limit), rnd.next(-limit, limit)});
        }
    }

    shuffle(points.begin(), points.end());
    println(static_cast<int>(points.size()));
    for (auto [x, y] : points) println(x, y);

    return 0;
}
