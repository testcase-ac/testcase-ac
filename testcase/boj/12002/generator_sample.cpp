#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x, int y) {
    if (x < 1 || x > 40000 || y < 1 || y > 40000) return;
    if (used.insert({x, y}).second) points.push_back({x, y});
}

static void fillRandom(vector<pair<int, int>>& points, set<pair<int, int>>& used, int n) {
    while ((int)points.size() < n) {
        addPoint(points, used, rnd.next(1, 40000), rnd.next(1, 40000));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(5, 28);
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    if (mode == 0) {
        int x = rnd.next(10, 39990);
        int y = rnd.next(10, 39990);
        int dx = rnd.next(0, 1);
        for (int i = 0; i < n; ++i) {
            int off = i + 1;
            addPoint(points, used, x + dx * off, y + (1 - dx) * off);
        }
    } else if (mode == 1) {
        int cx = rnd.next(100, 39900);
        int cy = rnd.next(100, 39900);
        int core = max(5, n - rnd.next(1, 3));
        for (int i = 0; i < core; ++i) {
            addPoint(points, used, cx + rnd.next(-7, 7), cy + rnd.next(-7, 7));
        }
        while ((int)points.size() < n) {
            int side = rnd.next(0, 3);
            int x = side == 0 ? rnd.next(1, 40) : side == 1 ? rnd.next(39960, 40000) : rnd.next(1, 40000);
            int y = side == 2 ? rnd.next(1, 40) : side == 3 ? rnd.next(39960, 40000) : rnd.next(1, 40000);
            addPoint(points, used, x, y);
        }
    } else if (mode == 2) {
        int minX = rnd.next(1, 20000);
        int minY = rnd.next(1, 20000);
        int maxX = rnd.next(minX + 1, 40000);
        int maxY = rnd.next(minY + 1, 40000);
        addPoint(points, used, minX, minY);
        addPoint(points, used, minX, maxY);
        addPoint(points, used, maxX, minY);
        addPoint(points, used, maxX, maxY);
        while ((int)points.size() < n) {
            addPoint(points, used, rnd.next(minX, maxX), rnd.next(minY, maxY));
        }
    } else if (mode == 3) {
        int baseX = rnd.next(20, 39980);
        int baseY = rnd.next(20, 39980);
        int stepX = rnd.next(1, 6);
        int stepY = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int jitter = rnd.next(-2, 2);
            addPoint(points, used, baseX + i * stepX, baseY + i * stepY + jitter);
        }
    } else {
        fillRandom(points, used, n);
    }

    fillRandom(points, used, n);
    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (auto [x, y] : points) println(x, y);

    return 0;
}
