#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addPoint(set<pair<int, int>>& points, int n, int r, int c) {
    r = max(1, min(n, r));
    c = max(1, min(r, c));
    points.insert({r, c});
}

static void fillRandom(set<pair<int, int>>& points, int n, int target) {
    while ((int)points.size() < target) {
        int r = rnd.next(1, n);
        int c = rnd.next(1, r);
        points.insert({r, c});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    set<pair<int, int>> points;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int target = rnd.next(1, min(30, n * (n + 1) / 2));
        fillRandom(points, n, target);
    } else if (mode == 1) {
        n = rnd.any(vector<int>{20, 50, 1000, 1000000000});
        int target = rnd.next(2, 18);
        for (int i = 0; i < target; ++i) {
            int c;
            if (i == 0) {
                c = 1;
            } else if (i == 1) {
                c = n;
            } else {
                c = rnd.next(1, n);
            }
            addPoint(points, n, n, c);
        }
        fillRandom(points, n, target);
    } else if (mode == 2) {
        n = rnd.next(8, 80);
        int target = rnd.next(4, 24);
        int c = rnd.next(1, n / 2);
        for (int i = 0; i < target; ++i) {
            int r = rnd.next(max(c, 1), n);
            addPoint(points, n, r, c);
            if (rnd.next(0, 2) == 0) {
                addPoint(points, n, r, min(r, c + rnd.next(0, 3)));
            }
        }
        fillRandom(points, n, target);
    } else if (mode == 3) {
        n = rnd.next(10, 120);
        int target = rnd.next(5, 28);
        int startR = rnd.next(1, n);
        int startC = rnd.next(1, startR);
        for (int i = 0; i < target; ++i) {
            int r = min(n, startR + i + rnd.next(0, 2));
            int c = min(r, startC + i + rnd.next(-1, 1));
            addPoint(points, n, r, c);
        }
        fillRandom(points, n, target);
    } else if (mode == 4) {
        n = rnd.next(15, 200);
        int target = rnd.next(8, 35);
        int centerR = rnd.next(5, n);
        int centerC = rnd.next(1, centerR);
        for (int i = 0; i < target; ++i) {
            int r = centerR + rnd.next(-4, 4);
            int c = centerC + rnd.next(-4, 4);
            addPoint(points, n, r, c);
        }
        fillRandom(points, n, target);
    } else {
        n = rnd.any(vector<int>{1000000000, 999999937, rnd.next(1000, 1000000)});
        int target = rnd.next(3, 20);
        addPoint(points, n, n, 1);
        addPoint(points, n, n, n);
        addPoint(points, n, n - 1, rnd.next(1, n - 1));
        while ((int)points.size() < target) {
            int r = n - rnd.next(0, 1000);
            int c = rnd.next(1, r);
            addPoint(points, n, r, c);
        }
    }

    vector<pair<int, int>> required(points.begin(), points.end());
    shuffle(required.begin(), required.end());

    println(n, (int)required.size());
    for (const auto& point : required) {
        println(point.first, point.second);
    }

    return 0;
}
