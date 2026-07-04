#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

const int kMaxCoord = 1000000;

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int r, int c) {
    if (used.insert({r, c}).second) {
        points.push_back({r, c});
    }
}

int randomCoordAwayFromEdges() {
    return rnd.next(20, kMaxCoord - 20);
}

vector<pair<int, int>> makeCross() {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int centerR = randomCoordAwayFromEdges();
    int centerC = randomCoordAwayFromEdges();
    addPoint(points, used, centerR, centerC);

    int arms = rnd.next(1, 4);
    for (int d = 1; d <= arms; ++d) {
        if (rnd.next(2)) addPoint(points, used, centerR - d, centerC);
        if (rnd.next(2)) addPoint(points, used, centerR + d, centerC);
        if (rnd.next(2)) addPoint(points, used, centerR, centerC - d);
        if (rnd.next(2)) addPoint(points, used, centerR, centerC + d);
    }

    return points;
}

vector<pair<int, int>> makeAlternatingChain() {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int r = randomCoordAwayFromEdges();
    int c = randomCoordAwayFromEdges();
    addPoint(points, used, r, c);

    int length = rnd.next(4, 12);
    for (int i = 1; i < length; ++i) {
        if (i % 2 == 1) {
            c += rnd.next(1, 6);
        } else {
            r += rnd.next(1, 6);
        }
        addPoint(points, used, r, c);
    }

    return points;
}

vector<pair<int, int>> makeDisjointGroups() {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int groups = rnd.next(2, 5);
    for (int g = 0; g < groups; ++g) {
        int baseR = 100 + g * 1000 + rnd.next(0, 50);
        int baseC = 200 + g * 1000 + rnd.next(0, 50);
        int type = rnd.next(3);

        if (type == 0) {
            int count = rnd.next(1, 4);
            for (int i = 0; i < count; ++i) {
                addPoint(points, used, baseR, baseC + i);
            }
        } else if (type == 1) {
            int count = rnd.next(1, 4);
            for (int i = 0; i < count; ++i) {
                addPoint(points, used, baseR + i, baseC);
            }
        } else {
            addPoint(points, used, baseR, baseC);
            addPoint(points, used, baseR + 1, baseC);
            addPoint(points, used, baseR, baseC + 1);
        }
    }

    return points;
}

vector<pair<int, int>> makeDenseRectangle() {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int rows = rnd.next(2, 5);
    int cols = rnd.next(2, 5);
    int baseR = randomCoordAwayFromEdges();
    int baseC = randomCoordAwayFromEdges();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (rnd.next(100) < 70) {
                addPoint(points, used, baseR + r, baseC + c);
            }
        }
    }

    if (points.empty()) {
        addPoint(points, used, baseR, baseC);
    }

    return points;
}

vector<pair<int, int>> makeBoundaryCase() {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    addPoint(points, used, 1, rnd.next(1, 5));
    addPoint(points, used, rnd.next(1, 5), 1);
    addPoint(points, used, kMaxCoord, kMaxCoord - rnd.next(0, 4));
    addPoint(points, used, kMaxCoord - rnd.next(0, 4), kMaxCoord);

    int extras = rnd.next(0, 4);
    for (int i = 0; i < extras; ++i) {
        addPoint(points, used, rnd.next(1, kMaxCoord), rnd.next(1, kMaxCoord));
    }

    return points;
}

vector<pair<int, int>> makeScattered() {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    int n = rnd.next(1, 12);
    while ((int)points.size() < n) {
        addPoint(points, used, rnd.next(1, kMaxCoord), rnd.next(1, kMaxCoord));
    }

    return points;
}

vector<pair<int, int>> makeCase() {
    int mode = rnd.next(6);
    if (mode == 0) return makeCross();
    if (mode == 1) return makeAlternatingChain();
    if (mode == 2) return makeDisjointGroups();
    if (mode == 3) return makeDenseRectangle();
    if (mode == 4) return makeBoundaryCase();
    return makeScattered();
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<pair<int, int>> points = makeCase();
        shuffle(points.begin(), points.end());

        println((int)points.size());
        for (const auto& point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}
