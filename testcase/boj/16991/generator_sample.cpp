#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 16 : 12);
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    auto addPoint = [&](int x, int y) {
        if (x < -1000 || x > 1000 || y < -1000 || y > 1000) return false;
        if (!used.insert({x, y}).second) return false;
        points.push_back({x, y});
        return true;
    };

    auto addRandomPoint = [&](int lo, int hi) {
        while ((int)points.size() < n) {
            addPoint(rnd.next(lo, hi), rnd.next(lo, hi));
        }
    };

    if (mode == 0) {
        addRandomPoint(-20, 20);
    } else if (mode == 1) {
        int x0 = rnd.next(-900, 900);
        int y0 = rnd.next(-900, 900);
        int dx = rnd.next(-8, 8);
        int dy = rnd.next(-8, 8);
        if (dx == 0 && dy == 0) dx = 1;
        for (int i = 0; i < n; ++i) {
            int jitter = rnd.next(-1, 1);
            addPoint(x0 + i * dx, y0 + i * dy + jitter);
        }
        addRandomPoint(-900, 900);
    } else if (mode == 2) {
        int side = rnd.next(2, 5);
        vector<pair<int, int>> cells;
        int baseX = rnd.next(-50, 50);
        int baseY = rnd.next(-50, 50);
        int step = rnd.next(1, 10);
        for (int i = 0; i < side; ++i) {
            for (int j = 0; j < side; ++j) {
                cells.push_back({baseX + i * step, baseY + j * step});
            }
        }
        shuffle(cells.begin(), cells.end());
        n = rnd.next(2, min(16, (int)cells.size()));
        for (int i = 0; i < n; ++i) addPoint(cells[i].first, cells[i].second);
    } else if (mode == 3) {
        vector<pair<int, int>> candidates = {
            {-1000, -1000}, {-1000, 1000}, {1000, -1000}, {1000, 1000},
            {-1000, 0},     {1000, 0},     {0, -1000},    {0, 1000},
            {-999, -999},   {-999, 999},   {999, -999},   {999, 999},
            {-1, 0},        {1, 0},        {0, -1},       {0, 1},
        };
        shuffle(candidates.begin(), candidates.end());
        n = rnd.next(2, 16);
        for (int i = 0; i < n; ++i) addPoint(candidates[i].first, candidates[i].second);
    } else if (mode == 4) {
        int clusters = rnd.next(2, 4);
        vector<pair<int, int>> centers;
        for (int i = 0; i < clusters; ++i) {
            centers.push_back({rnd.next(-800, 800), rnd.next(-800, 800)});
        }
        while ((int)points.size() < n) {
            auto center = rnd.any(centers);
            addPoint(center.first + rnd.next(-8, 8), center.second + rnd.next(-8, 8));
        }
    } else {
        n = 16;
        addPoint(-1000, -1000);
        addPoint(-1000, 1000);
        addPoint(1000, -1000);
        addPoint(1000, 1000);
        addRandomPoint(-1000, 1000);
    }

    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
