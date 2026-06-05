#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const int MIN_COORD = -10000;
const int MAX_COORD = 10000;

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x, int y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

pair<int, int> randomUnusedPoint(set<pair<int, int>>& used) {
    while (true) {
        int x = rnd.next(MIN_COORD, MAX_COORD);
        int y = rnd.next(MIN_COORD, MAX_COORD);
        if (used.insert({x, y}).second) {
            return {x, y};
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 3;
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(3, 8);
        int startX = rnd.next(-5, 5);
        int startY = rnd.next(-5, 5);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, startX + rnd.next(-2, 2), startY + rnd.next(-2, 2));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        int y = rnd.next(MIN_COORD, MAX_COORD);
        int left = rnd.next(MIN_COORD, -9990);
        int step = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, left + i * step, y);
        }
    } else if (mode == 2) {
        n = rnd.next(4, 16);
        int x = rnd.next(-20, 20);
        int step = rnd.next(1, 6);
        int bottom = rnd.next(-10000, 10000 - step * (n - 1));
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, x, bottom + i * step);
        }
    } else if (mode == 3) {
        int width = rnd.next(2, 5);
        int height = rnd.next(2, 5);
        n = rnd.next(3, width * height);
        int baseX = rnd.next(-20, 20);
        int baseY = rnd.next(-20, 20);
        int gap = rnd.next(1, 5);
        vector<pair<int, int>> grid;
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                grid.push_back({baseX + i * gap, baseY + j * gap});
            }
        }
        shuffle(grid.begin(), grid.end());
        for (int i = 0; i < n; ++i) {
            addPoint(points, used, grid[i].first, grid[i].second);
        }
    } else if (mode == 4) {
        n = rnd.next(3, 20);
        vector<pair<int, int>> corners = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
            {0, 0},
        };
        shuffle(corners.begin(), corners.end());
        for (auto p : corners) {
            addPoint(points, used, p.first, p.second);
        }
    } else {
        n = rnd.next(20, 80);
    }

    while ((int)points.size() < n) {
        points.push_back(randomUnusedPoint(used));
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (auto p : points) {
        println(p.first, p.second);
    }

    return 0;
}
