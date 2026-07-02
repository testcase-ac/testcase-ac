#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

bool withinDistance(Point a, Point b, int d) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return dx * dx + dy * dy <= d * d;
}

bool validWithDegreeLimit(const vector<Point>& points, int d) {
    set<Point> seen;
    for (Point p : points) {
        if (p.first < 0 || p.first >= 1000 || p.second < 0 || p.second >= 1000) {
            return false;
        }
        if (!seen.insert(p).second) {
            return false;
        }
    }

    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        int neighbors = 0;
        for (int j = 0; j < static_cast<int>(points.size()); ++j) {
            if (i != j && withinDistance(points[i], points[j], d)) {
                ++neighbors;
            }
        }
        if (neighbors > 10) {
            return false;
        }
    }
    return true;
}

void addSparseRandomPoint(vector<Point>& points, int d) {
    for (int attempt = 0; attempt < 10000; ++attempt) {
        Point candidate = {rnd.next(0, 999), rnd.next(0, 999)};
        vector<Point> next = points;
        next.push_back(candidate);
        if (validWithDegreeLimit(next, d)) {
            points = next;
            return;
        }
    }
    ensuref(false, "failed to place a sparse random city");
}

vector<Point> makeChain(int length, int d, int baseX, int baseY) {
    vector<Point> points;
    points.reserve(length);
    for (int i = 0; i < length; ++i) {
        points.push_back({baseX + i * d, baseY});
    }
    return points;
}

vector<Point> makeCluster(int d) {
    vector<Point> points = {{500, 500}};
    vector<Point> candidates;
    for (int dx = -d; dx <= d; ++dx) {
        for (int dy = -d; dy <= d; ++dy) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            if (dx * dx + dy * dy <= d * d) {
                candidates.push_back({500 + dx, 500 + dy});
            }
        }
    }

    shuffle(candidates.begin(), candidates.end());
    int leaves = rnd.next(1, min(10, static_cast<int>(candidates.size())));
    for (int i = 0; i < leaves; ++i) {
        points.push_back(candidates[i]);
    }
    return points;
}

void printCase(const vector<Point>& points, int m, int d, int k) {
    println(static_cast<int>(points.size()));
    println(m);
    println(d);
    println(k);
    for (Point p : points) {
        println(p.first, p.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int d = rnd.next(1, 25);
    int m = rnd.next(1, 100);
    int k = rnd.next(1, 100);
    vector<Point> points;

    if (mode == 0) {
        points.push_back({rnd.next(0, 999), rnd.next(0, 999)});
    } else if (mode == 1) {
        int length = rnd.next(2, min(20, 1 + 999 / d));
        int baseX = rnd.next(0, 999 - (length - 1) * d);
        int baseY = rnd.next(0, 999);
        points = makeChain(length, d, baseX, baseY);
    } else if (mode == 2) {
        int firstLength = rnd.next(2, min(12, 1 + 450 / d));
        int secondLength = rnd.next(2, min(12, 1 + 450 / d));
        points = makeChain(firstLength, d, 10, rnd.next(20, 200));
        vector<Point> second = makeChain(secondLength, d, 540, rnd.next(600, 900));
        points.insert(points.end(), second.begin(), second.end());
        int extra = rnd.next(0, 5);
        for (int i = 0; i < extra; ++i) {
            addSparseRandomPoint(points, d);
        }
    } else if (mode == 3) {
        points = makeCluster(d);
    } else {
        int n = rnd.next(2, 35);
        while (static_cast<int>(points.size()) < n) {
            addSparseRandomPoint(points, d);
        }
    }

    ensure(validWithDegreeLimit(points, d));
    printCase(points, m, d, k);
    return 0;
}
