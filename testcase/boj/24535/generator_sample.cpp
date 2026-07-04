#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

constexpr int kMinCoord = -1000000000;
constexpr int kMaxCoord = 1000000000;

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x,
              int y) {
    if (used.insert({x, y}).second) {
        points.push_back({x, y});
    }
}

int randomCoord(int span) {
    return rnd.next(-span, span);
}

vector<pair<int, int>> makeSinglePoint() {
    set<pair<int, int>> used;
    vector<pair<int, int>> points;
    addPoint(points, used, rnd.any(vector<int>{kMinCoord, -7, 0, 9, kMaxCoord}),
             rnd.any(vector<int>{kMinCoord, -11, 0, 13, kMaxCoord}));
    return points;
}

vector<pair<int, int>> makeLine() {
    set<pair<int, int>> used;
    vector<pair<int, int>> points;
    int n = rnd.next(2, 18);
    bool vertical = rnd.next(2) == 0;
    int fixed = randomCoord(30);

    while ((int)points.size() < n) {
        int moving = randomCoord(45);
        int x = vertical ? fixed : moving;
        int y = vertical ? moving : fixed;
        addPoint(points, used, x, y);
    }
    return points;
}

vector<pair<int, int>> makeRectanglePerimeter() {
    set<pair<int, int>> used;
    vector<pair<int, int>> points;
    int x1 = randomCoord(35);
    int x2 = x1 + rnd.next(1, 18);
    int y1 = randomCoord(35);
    int y2 = y1 + rnd.next(1, 18);

    for (int x = x1; x <= x2; ++x) {
        if (rnd.next(100) < 75) {
            addPoint(points, used, x, y1);
        }
        if (rnd.next(100) < 75) {
            addPoint(points, used, x, y2);
        }
    }
    for (int y = y1; y <= y2; ++y) {
        if (rnd.next(100) < 75) {
            addPoint(points, used, x1, y);
        }
        if (rnd.next(100) < 75) {
            addPoint(points, used, x2, y);
        }
    }

    int noise = rnd.next(0, 8);
    while (noise--) {
        addPoint(points, used, randomCoord(60), randomCoord(60));
    }
    if (points.empty()) {
        addPoint(points, used, x1, y1);
    }
    return points;
}

vector<pair<int, int>> makeSparseGrid() {
    set<pair<int, int>> used;
    vector<pair<int, int>> points;
    int rows = rnd.next(2, 7);
    int cols = rnd.next(2, 7);
    int baseX = randomCoord(20);
    int baseY = randomCoord(20);
    int stepX = rnd.next(1, 9);
    int stepY = rnd.next(1, 9);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (rnd.next(100) < 55) {
                addPoint(points, used, baseX + i * stepX, baseY + j * stepY);
            }
        }
    }
    if (points.empty()) {
        addPoint(points, used, baseX, baseY);
    }
    return points;
}

vector<pair<int, int>> makeExtremeMix() {
    set<pair<int, int>> used;
    vector<pair<int, int>> points;
    vector<int> coords = {kMinCoord, kMinCoord + 1, -1, 0,
                          1,         kMaxCoord - 1, kMaxCoord};
    int n = rnd.next(4, 14);
    while ((int)points.size() < n) {
        int x = rnd.next(100) < 70 ? rnd.any(coords) : randomCoord(100);
        int y = rnd.next(100) < 70 ? rnd.any(coords) : randomCoord(100);
        addPoint(points, used, x, y);
    }
    return points;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> points;
    int mode = rnd.next(5);
    if (mode == 0) {
        points = makeSinglePoint();
    } else if (mode == 1) {
        points = makeLine();
    } else if (mode == 2) {
        points = makeRectanglePerimeter();
    } else if (mode == 3) {
        points = makeSparseGrid();
    } else {
        points = makeExtremeMix();
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (const auto& point : points) {
        println(point.first, point.second);
    }

    return 0;
}
