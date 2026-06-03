#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampCoord(int x) {
    return max(1, min(30000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 18);

    vector<pair<int, int>> points;
    points.reserve(n);

    if (mode == 0) {
        int y = rnd.next(1, 30000);
        int start = rnd.next(1, 29960);
        int step = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            points.push_back({clampCoord(start + i * step), y});
        }
    } else if (mode == 1) {
        int width = rnd.next(2, 5);
        int step = rnd.next(2, 9);
        int baseX = rnd.next(1, 29950);
        int baseY = rnd.next(1, 29950);
        for (int i = 0; i < n; ++i) {
            points.push_back({
                clampCoord(baseX + (i % width) * step),
                clampCoord(baseY + (i / width) * step)
            });
        }
    } else if (mode == 2) {
        int baseX = rnd.next(20, 29980);
        int baseY = rnd.next(20, 29980);
        for (int i = 0; i < n; ++i) {
            points.push_back({
                clampCoord(baseX + rnd.next(-12, 12)),
                clampCoord(baseY + rnd.next(-12, 12))
            });
        }
    } else if (mode == 3) {
        int ax = rnd.next(1, 10000);
        int ay = rnd.next(1, 10000);
        int bx = rnd.next(20000, 30000);
        int by = rnd.next(20000, 30000);
        for (int i = 0; i < n; ++i) {
            bool first = rnd.next(2) == 0;
            points.push_back({
                clampCoord((first ? ax : bx) + rnd.next(-8, 8)),
                clampCoord((first ? ay : by) + rnd.next(-8, 8))
            });
        }
    } else {
        for (int i = 0; i < n; ++i) {
            points.push_back({rnd.next(1, 30000), rnd.next(1, 30000)});
        }
    }

    shuffle(points.begin(), points.end());

    vector<int> marked;
    marked.reserve(m);
    for (int i = 0; i < m; ++i) {
        if (i < n && rnd.next(100) < 65) {
            marked.push_back(i + 1);
        } else {
            marked.push_back(rnd.next(1, n));
        }
    }
    shuffle(marked.begin(), marked.end());

    vector<int> radii;
    radii.reserve(m + 1);
    int family = rnd.next(4);
    for (int i = 0; i <= m; ++i) {
        if (family == 0) {
            radii.push_back(rnd.next(1, 8));
        } else if (family == 1) {
            radii.push_back(rnd.next(5, 25));
        } else if (family == 2) {
            radii.push_back(rnd.next(20, 120));
        } else {
            radii.push_back(rnd.next(1, 30000));
        }
    }

    println(n, m);
    for (auto point : points) {
        println(point.first, point.second);
    }
    println(marked);
    println(radii);

    return 0;
}
