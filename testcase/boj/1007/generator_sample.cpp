#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

const int LIM = 100000;

void addPoint(vector<pair<int, int>>& points, set<pair<int, int>>& used, int x, int y) {
    if (used.insert({x, y}).second)
        points.push_back({x, y});
}

int randomCoord(int span) {
    return rnd.next(-span, span);
}

pair<int, int> randomUnusedPoint(set<pair<int, int>>& used, int span) {
    while (true) {
        pair<int, int> p = {randomCoord(span), randomCoord(span)};
        if (used.insert(p).second)
            return p;
    }
}

vector<pair<int, int>> makeSymmetric(int n) {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;
    int span = rnd.next(20, LIM);

    while ((int)points.size() + 1 < n) {
        auto p = randomUnusedPoint(used, span);
        pair<int, int> q = {-p.first, -p.second};
        if (used.insert(q).second) {
            points.push_back(p);
            points.push_back(q);
        }
    }

    while ((int)points.size() < n) {
        auto p = randomUnusedPoint(used, span);
        points.push_back(p);
    }
    return points;
}

vector<pair<int, int>> makeBoundary(int n) {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;
    vector<pair<int, int>> candidates = {
        {-LIM, -LIM}, {-LIM, LIM}, {LIM, -LIM}, {LIM, LIM},
        {-LIM, 0}, {LIM, 0}, {0, -LIM}, {0, LIM},
        {-LIM + 1, LIM - 1}, {LIM - 1, -LIM + 1}
    };
    shuffle(candidates.begin(), candidates.end());

    for (auto p : candidates) {
        if ((int)points.size() == n)
            break;
        addPoint(points, used, p.first, p.second);
    }

    while ((int)points.size() < n) {
        int x = rnd.any(vector<int>{-LIM, LIM, rnd.next(-LIM, LIM)});
        int y = rnd.any(vector<int>{-LIM, LIM, rnd.next(-LIM, LIM)});
        auto p = make_pair(x, y);
        if (used.insert(p).second)
            points.push_back(p);
    }
    return points;
}

vector<pair<int, int>> makeClustered(int n) {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;
    int cx = rnd.next(-90000, 90000);
    int cy = rnd.next(-90000, 90000);
    int radius = rnd.next(1, 400);

    while ((int)points.size() < n) {
        int x = cx + rnd.next(-radius, radius);
        int y = cy + rnd.next(-radius, radius);
        if (x < -LIM || x > LIM || y < -LIM || y > LIM)
            continue;
        auto p = make_pair(x, y);
        if (used.insert(p).second)
            points.push_back(p);
    }
    return points;
}

vector<pair<int, int>> makeRandomCase(int n) {
    vector<pair<int, int>> points;
    set<pair<int, int>> used;
    int span = rnd.next(5, LIM);

    while ((int)points.size() < n) {
        auto p = randomUnusedPoint(used, span);
        points.push_back(p);
    }
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 7);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == t - 1) {
            n = 20;
        } else {
            n = 2 * rnd.next(1, 8);
        }

        vector<pair<int, int>> points;
        int mode = tc % 4;
        if (mode == 0) {
            points = makeSymmetric(n);
        } else if (mode == 1) {
            points = makeBoundary(n);
        } else if (mode == 2) {
            points = makeClustered(n);
        } else {
            points = makeRandomCase(n);
        }

        shuffle(points.begin(), points.end());
        println(n);
        for (auto p : points)
            println(p.first, p.second);
    }

    return 0;
}
