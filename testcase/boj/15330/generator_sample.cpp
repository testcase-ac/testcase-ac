#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

long long cross(const pair<int, int>& a,
                const pair<int, int>& b,
                const pair<int, int>& c) {
    long long abx = b.first - a.first;
    long long aby = b.second - a.second;
    long long acx = c.first - a.first;
    long long acy = c.second - a.second;
    return abx * acy - aby * acx;
}

bool isValid(const vector<pair<int, int>>& points) {
    set<pair<int, int>> seen(points.begin(), points.end());
    if (seen.size() != points.size()) return false;

    for (int i = 0; i < int(points.size()); ++i) {
        if (points[i].first < -1000 || points[i].first > 1000) return false;
        if (points[i].second < -1000 || points[i].second > 1000) return false;
        for (int j = i + 1; j < int(points.size()); ++j) {
            for (int k = j + 1; k < int(points.size()); ++k) {
                if (cross(points[i], points[j], points[k]) == 0) return false;
            }
        }
    }
    return true;
}

vector<pair<int, int>> randomPoints(int m, int lo, int hi) {
    vector<pair<int, int>> points;
    for (int attempt = 0; attempt < 20000; ++attempt) {
        points.clear();
        set<pair<int, int>> seen;
        while (int(points.size()) < m) {
            pair<int, int> point = {rnd.next(lo, hi), rnd.next(lo, hi)};
            if (seen.insert(point).second) points.push_back(point);
        }
        if (isValid(points)) return points;
    }
    return points;
}

vector<pair<int, int>> parallelPairs(int m, int lo, int hi) {
    vector<pair<int, int>> points;
    vector<pair<int, int>> directions = {
        {1, 0}, {0, 1}, {1, 1}, {1, -1}, {2, 1}, {1, 2}, {3, -1}};
    pair<int, int> dir = rnd.any(directions);
    int scale = rnd.next(1, max(1, (hi - lo) / 8));
    dir.first *= scale;
    dir.second *= scale;

    for (int attempt = 0; attempt < 20000; ++attempt) {
        points.clear();
        for (int i = 0; i < m / 2; ++i) {
            int x = rnd.next(lo, hi);
            int y = rnd.next(lo, hi);
            points.push_back({x, y});
            points.push_back({x + dir.first, y + dir.second});
        }
        if (isValid(points)) return points;
    }
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int m = 2 * rnd.next(1, 8);
    vector<pair<int, int>> points;

    if (mode == 0) {
        points = randomPoints(m, -8, 8);
    } else if (mode == 1) {
        points = parallelPairs(m, -20, 20);
    } else if (mode == 2) {
        points = parallelPairs(m, -100, 100);
    } else {
        points = randomPoints(m, -1000, 1000);
    }

    if (!isValid(points)) points = randomPoints(m, -1000, 1000);
    shuffle(points.begin(), points.end());

    println(m);
    for (const auto& point : points) println(point.first, point.second);

    return 0;
}
