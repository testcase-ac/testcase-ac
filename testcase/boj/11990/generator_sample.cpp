#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int oddInRange(int lo, int hi) {
    int a = (lo + 1) / 2;
    int b = (hi + 1) / 2;
    return 2 * rnd.next(a, b) - 1;
}

void addPoint(set<pair<int, int>>& used, vector<pair<int, int>>& points, int x, int y) {
    if (used.insert({x, y}).second) points.push_back({x, y});
}

void addRandomPoint(set<pair<int, int>>& used, vector<pair<int, int>>& points, int lo, int hi) {
    while (true) {
        int x = oddInRange(lo, hi);
        int y = oddInRange(lo, hi);
        if (used.insert({x, y}).second) {
            points.push_back({x, y});
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int targetN = rnd.next(1, 60);
    set<pair<int, int>> used;
    vector<pair<int, int>> points;

    if (mode == 0) {
        targetN = rnd.next(1, 15);
        for (int i = 0; i < targetN; ++i) addRandomPoint(used, points, 1, 39);
    } else if (mode == 1) {
        int xs = rnd.next(1, 8);
        int ys = rnd.next(1, 8);
        vector<int> xvals, yvals;
        for (int i = 0; i < xs; ++i) xvals.push_back(2 * i + 1);
        for (int i = 0; i < ys; ++i) yvals.push_back(2 * i + 1);
        vector<pair<int, int>> candidates;
        for (int x : xvals)
            for (int y : yvals) candidates.push_back({x, y});
        shuffle(candidates.begin(), candidates.end());
        targetN = rnd.next(1, (int)candidates.size());
        for (int i = 0; i < targetN; ++i) addPoint(used, points, candidates[i].first, candidates[i].second);
    } else if (mode == 2) {
        targetN = rnd.next(8, 40);
        vector<pair<int, int>> centers = {{101, 101}, {101, 501}, {501, 101}, {501, 501}};
        for (int i = 0; i < targetN; ++i) {
            auto center = rnd.any(centers);
            int x = center.first + 2 * rnd.next(-5, 5);
            int y = center.second + 2 * rnd.next(-5, 5);
            addPoint(used, points, x, y);
        }
    } else if (mode == 3) {
        targetN = rnd.next(4, 30);
        for (int i = 0; i < targetN; ++i) {
            int base = 2 * i + 1;
            int jitter = 2 * rnd.next(0, 3);
            addPoint(used, points, base, base + jitter);
        }
    } else if (mode == 4) {
        targetN = rnd.next(4, 24);
        for (int i = 0; i < targetN; ++i) {
            int x = (i % 2 == 0) ? oddInRange(1, 25) : oddInRange(999975, 999999);
            int y = (i % 3 == 0) ? oddInRange(1, 25) : oddInRange(999975, 999999);
            addPoint(used, points, x, y);
        }
    } else {
        targetN = rnd.next(6, 50);
        int sharedX = oddInRange(1, 31);
        int sharedY = oddInRange(101, 151);
        for (int i = 0; i < targetN; ++i) {
            int x = (rnd.next(0, 1) == 0) ? sharedX : oddInRange(1, 199);
            int y = (rnd.next(0, 1) == 0) ? sharedY : oddInRange(1, 199);
            addPoint(used, points, x, y);
        }
    }

    while ((int)points.size() < targetN) addRandomPoint(used, points, 1, 999999);
    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (auto [x, y] : points) println(x, y);

    return 0;
}
