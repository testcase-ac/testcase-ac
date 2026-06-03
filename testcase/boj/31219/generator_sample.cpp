#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

bool validPoints(const vector<Point>& points) {
    set<Point> seen(points.begin(), points.end());
    if (seen.size() != points.size()) return false;

    int n = points.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                long long x1 = points[j].first - points[i].first;
                long long y1 = points[j].second - points[i].second;
                long long x2 = points[k].first - points[i].first;
                long long y2 = points[k].second - points[i].second;
                if (x1 * y2 == x2 * y1) return false;
            }
        }
    }

    return true;
}

vector<Point> randomCloud(int n, int limit) {
    vector<Point> points;
    while ((int)points.size() < n) {
        points.push_back({rnd.next(-limit, limit), rnd.next(-limit, limit)});
        if (!validPoints(points)) points.pop_back();
    }
    return points;
}

vector<Point> parabolaPoints(int n, int step, int shiftX, int shiftY) {
    vector<int> xs;
    for (int i = -12; i <= 12; ++i) xs.push_back(i);
    shuffle(xs.begin(), xs.end());

    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        int x = xs[i] * step + shiftX;
        int y = xs[i] * xs[i] * step + shiftY;
        points.push_back({x, y});
    }
    return points;
}

vector<Point> boundaryMix(int n) {
    vector<Point> candidates = {
        {-1000000, -999999},
        {-999999, 1000000},
        {999998, 999999},
        {1000000, -1000000},
        {-500000, 123457},
        {123456, -654321},
        {777777, 333331},
        {-222223, -777779},
        {0, 999983},
        {999979, 0},
    };
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(n);
    if (validPoints(candidates)) return candidates;
    return randomCloud(n, 1000000);
}

vector<Point> ringPoints(int n) {
    vector<Point> candidates = {
        {0, 11},
        {7, 9},
        {11, 2},
        {8, -8},
        {1, -11},
        {-6, -10},
        {-11, -3},
        {-9, 6},
        {-3, 11},
        {10, -1},
    };
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(n);
    return candidates;
}

void printCase(vector<Point> points) {
    ensuref(validPoints(points), "generator produced invalid points");
    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (auto [x, y] : points) println(x, y);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 10);
    vector<Point> points;

    if (mode == 0) {
        points = randomCloud(n, rnd.next(2, 20));
    } else if (mode == 1) {
        points = randomCloud(n, rnd.next(50, 5000));
    } else if (mode == 2) {
        points = ringPoints(n);
    } else if (mode == 3) {
        points = boundaryMix(n);
    } else {
        points = parabolaPoints(n, rnd.next(1, 5000), rnd.next(-1000, 1000),
                               rnd.next(-1000, 1000));
    }

    printCase(points);
    return 0;
}
