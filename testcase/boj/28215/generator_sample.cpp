#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    int k = rnd.next(1, min(3, n));

    vector<pair<int, int>> points;
    set<pair<int, int>> used;
    auto addPoint = [&](int x, int y) {
        x = max(0, min(100000, x));
        y = max(0, min(100000, y));
        if (used.insert({x, y}).second) points.push_back({x, y});
    };

    if (mode == 0) {
        n = rnd.next(1, 20);
        k = rnd.next(1, min(3, n));
        int start = rnd.next(0, 200);
        int step = rnd.next(1, 80);
        int y = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) addPoint(start + i * step, y);
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        k = rnd.next(1, 3);
        vector<pair<int, int>> centers = {
            {rnd.next(0, 200), rnd.next(0, 200)},
            {rnd.next(900, 1200), rnd.next(0, 250)},
            {rnd.next(300, 650), rnd.next(700, 1000)}
        };
        while ((int)points.size() < n) {
            auto center = rnd.any(centers);
            addPoint(center.first + rnd.next(-25, 25),
                     center.second + rnd.next(-25, 25));
        }
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        k = rnd.next(1, min(3, n));
        int loX = rnd.next(0, 1000);
        int loY = rnd.next(0, 1000);
        int width = rnd.next(1, 1000);
        int height = rnd.next(1, 1000);
        vector<pair<int, int>> anchors = {
            {loX, loY},
            {loX + width, loY},
            {loX, loY + height},
            {loX + width, loY + height},
            {loX + width / 2, loY + height / 2}
        };
        shuffle(anchors.begin(), anchors.end());
        for (auto p : anchors) addPoint(p.first, p.second);
        while ((int)points.size() < n) {
            addPoint(rnd.next(loX, loX + width), rnd.next(loY, loY + height));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        k = rnd.next(1, min(3, n));
        addPoint(0, 0);
        addPoint(100000, 100000);
        while ((int)points.size() < n) {
            addPoint(rnd.next(0, 100000), rnd.next(0, 100000));
        }
    } else {
        n = rnd.next(1, 50);
        k = rnd.next(1, min(3, n));
        while ((int)points.size() < n) {
            addPoint(rnd.next(0, 5000), rnd.next(0, 5000));
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size(), k);
    for (auto p : points) println(p.first, p.second);

    return 0;
}
