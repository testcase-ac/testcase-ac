#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 0;
    int m = 1;
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    auto addPoint = [&](int x, int y) {
        if (x < 0 || x > 300 || y < 0 || y > 300) return;
        if (x == 0 && y == 0) return;
        if (used.insert({x, y}).second) points.push_back({x, y});
    };

    if (mode == 0) {
        n = 0;
        m = rnd.next(1, 1000000);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = rnd.any(vector<int>{1, 2, 3, 5, 10, 1000000});
        while ((int)points.size() < n) addPoint(rnd.next(0, 8), rnd.next(0, 8));
    } else if (mode == 2) {
        n = rnd.next(4, 14);
        m = rnd.next(1, 40);
        int limit = rnd.next(6, 18);
        while ((int)points.size() < n) {
            int x = rnd.next(0, limit);
            int y = rnd.next(0, limit - x);
            addPoint(x, y);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        m = rnd.next(5, 120);
        for (int i = 0; (int)points.size() < n && i < 400; ++i) {
            if (rnd.next(0, 1) == 0) addPoint(rnd.next(1, 300), 0);
            else addPoint(0, rnd.next(1, 300));
        }
    } else if (mode == 4) {
        n = rnd.next(8, 24);
        m = rnd.next(50, 700);
        int band = rnd.next(40, 300);
        while ((int)points.size() < n) {
            int x = rnd.next(0, band);
            int y = max(0, min(300, band - x + rnd.next(-3, 3)));
            addPoint(x, y);
        }
    } else if (mode == 5) {
        n = rnd.next(20, 60);
        m = rnd.next(1, 1000000);
        while ((int)points.size() < n) addPoint(rnd.next(0, 300), rnd.next(0, 300));
    } else {
        n = rnd.next(80, 300);
        m = rnd.next(300, 1000000);
        for (int x = 0; x <= 300 && (int)points.size() < n; ++x) {
            for (int y = 0; y <= 300 && (int)points.size() < n; ++y) {
                if (rnd.next(0, 9) == 0) addPoint(x, y);
            }
        }
        while ((int)points.size() < n) addPoint(rnd.next(0, 300), rnd.next(0, 300));
    }

    shuffle(points.begin(), points.end());

    println((int)points.size(), m);
    for (auto [x, y] : points) println(x, y);

    return 0;
}
