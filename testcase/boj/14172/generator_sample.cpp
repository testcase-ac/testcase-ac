#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <tuple>
#include <vector>

using namespace std;

struct Cow {
    int x;
    int y;
    int p;
};

int distCeil(const Cow& a, const Cow& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return static_cast<int>(ceil(sqrt(static_cast<double>(dx * dx + dy * dy))));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<Cow> cows;

    if (mode == 0) {
        int x = rnd.next(0, 25000);
        int y = rnd.next(0, 25000);
        for (int i = 0; i < n; ++i) cows.push_back({x, y, rnd.next(0, 3)});
    } else if (mode == 1) {
        int step = rnd.next(1, 12);
        int startX = rnd.next(0, 25000 - step * (n - 1));
        int y = rnd.next(0, 25000);
        for (int i = 0; i < n; ++i) {
            int p = (i + 1 == n ? rnd.next(0, step - 1) : rnd.next(step, step + 2));
            cows.push_back({startX + step * i, y, p});
        }
    } else if (mode == 2) {
        int side = rnd.next(2, 6);
        int baseX = rnd.next(0, 25000 - side * 5);
        int baseY = rnd.next(0, 25000 - side * 5);
        n = rnd.next(4, min(18, side * side));
        vector<pair<int, int>> points;
        for (int i = 0; i < side; ++i)
            for (int j = 0; j < side; ++j)
                points.push_back({baseX + 5 * i, baseY + 5 * j});
        shuffle(points.begin(), points.end());
        for (int i = 0; i < n; ++i) cows.push_back({points[i].first, points[i].second, rnd.next(0, 12)});
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int block = i % 3;
            int base = block * 8000;
            cows.push_back({base + rnd.next(0, 20), base + rnd.next(0, 20), rnd.next(0, 25)});
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) cows.push_back({rnd.next(0, 25000), rnd.next(0, 25000), rnd.next(0, 20)});
        int hub = rnd.next(n);
        cows[hub].p = 50000;
    } else {
        n = rnd.next(2, 18);
        int x = rnd.next(0, 25000);
        int y = rnd.next(0, 25000);
        cows.push_back({x, y, 0});
        for (int i = 1; i < n; ++i) {
            x = min(25000, x + rnd.next(1, 30));
            y = min(25000, y + rnd.next(0, 10));
            cows.push_back({x, y, 0});
            cows[i - 1].p = rnd.next(distCeil(cows[i - 1], cows[i]), 50000);
        }
    }

    shuffle(cows.begin(), cows.end());

    println(static_cast<int>(cows.size()));
    for (const Cow& cow : cows) println(cow.x, cow.y, cow.p);

    return 0;
}
