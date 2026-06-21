#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static vector<pair<int, int>> makeCollinearPoints(int n) {
    int dx = rnd.next(1, 7);
    int dy = rnd.next(-7, 7);
    int x0 = rnd.next(-20, 20);
    int y0 = rnd.next(-20, 20);

    vector<pair<int, int>> points;
    for (int i = 0; i < n; ++i) {
        points.push_back({x0 + i * dx, y0 + i * dy});
    }
    return points;
}

static vector<pair<int, int>> makeGridPoints(int n) {
    vector<pair<int, int>> candidates;
    int width = rnd.next(2, 5);
    int x0 = rnd.next(-10, 10);
    int y0 = rnd.next(-10, 10);
    int step = rnd.next(1, 5);

    for (int y = 0; static_cast<int>(candidates.size()) < n + 8; ++y) {
        for (int x = 0; x < width; ++x) {
            candidates.push_back({x0 + x * step, y0 + y * step});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(n);
    return candidates;
}

static vector<pair<int, int>> makeRandomPoints(int n) {
    set<pair<int, int>> used;
    int lo = rnd.next(-30, -5);
    int hi = rnd.next(5, 30);

    while (static_cast<int>(used.size()) < n) {
        used.insert({rnd.next(lo, hi), rnd.next(lo, hi)});
    }
    return vector<pair<int, int>>(used.begin(), used.end());
}

static void addExtremePoint(vector<pair<int, int>>& points) {
    vector<pair<int, int>> extremes = {
        {-1000000, -1000000},
        {-1000000, 1000000},
        {1000000, -1000000},
        {1000000, 1000000},
    };
    shuffle(extremes.begin(), extremes.end());

    for (const auto& point : extremes) {
        if (find(points.begin(), points.end(), point) == points.end()) {
            points[0] = point;
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int mode = rnd.next(0, 2);

    vector<pair<int, int>> points;
    if (mode == 0) {
        points = makeCollinearPoints(n);
    } else if (mode == 1) {
        points = makeGridPoints(n);
    } else {
        points = makeRandomPoints(n);
    }

    if (n > 1 && rnd.next(0, 4) == 0) {
        addExtremePoint(points);
    }
    shuffle(points.begin(), points.end());

    vector<pair<int, int>> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maxEdges = static_cast<int>(candidates.size());
    int m;
    if (maxEdges == 0) {
        m = 0;
    } else if (rnd.next(0, 4) == 0) {
        m = rnd.next(0, min(maxEdges, n - 1));
    } else {
        m = rnd.next(0, min(maxEdges, 20));
    }
    candidates.resize(m);

    println(n, m);
    for (const auto& point : points) {
        println(point.first, point.second);
    }
    for (auto edge : candidates) {
        if (rnd.next(0, 1) == 1) {
            swap(edge.first, edge.second);
        }
        println(edge.first, edge.second);
    }

    return 0;
}
