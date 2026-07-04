#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

const int MAX_XY = 1000;
const int MAX_DT = 10000;

pair<int, int> pointNearDistance(int target) {
    target = max(2, min(1414, target));

    for (int tries = 0; tries < 200; ++tries) {
        int x = rnd.next(1, MAX_XY);
        int y = rnd.next(1, MAX_XY);
        double dist = hypot((double)x, (double)y);
        if (abs(dist - target) <= max(2, target / 20)) return {x, y};
    }

    int x = min(MAX_XY, max(1, target));
    int y = rnd.next(1, min(MAX_XY, max(1, target / 8)));
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int x = rnd.next(1, MAX_XY);
    int y = rnd.next(1, MAX_XY);
    int d = rnd.next(1, MAX_DT);
    int t = rnd.next(1, MAX_DT);

    if (mode == 0) {
        d = rnd.next(1, 30);
        t = rnd.next(d + 1, min(MAX_DT, d + 200));
        auto point = pointNearDistance(rnd.next(2, 80));
        x = point.first;
        y = point.second;
    } else if (mode == 1) {
        d = rnd.next(2, 80);
        t = rnd.next(1, d);
        int multiplier = rnd.next(1, 12);
        auto point = pointNearDistance(d * multiplier + rnd.next(-2, 2));
        x = point.first;
        y = point.second;
    } else if (mode == 2) {
        auto point = pointNearDistance(rnd.next(2, 120));
        x = point.first;
        y = point.second;
        d = rnd.next((int)ceil(hypot((double)x, (double)y)) + 1, MAX_DT);
        t = rnd.next(1, min(MAX_DT, max(1, d / 2)));
    } else if (mode == 3) {
        auto point = rnd.any(vector<pair<int, int>>{
            {1, 1},
            {1, 1000},
            {1000, 1},
            {1000, 1000},
            {999, 1000},
        });
        x = point.first;
        y = point.second;
        d = rnd.any(vector<int>{1, 2, 999, 1000, 1414, 10000});
        t = rnd.any(vector<int>{1, 2, 9999, 10000, rnd.next(1, MAX_DT)});
    } else if (mode == 4) {
        d = rnd.next(200, 1500);
        int target = d * rnd.next(1, 2) + rnd.next(-5, 5);
        auto point = pointNearDistance(target);
        x = point.first;
        y = point.second;
        t = rnd.next(1, 20);
    } else if (mode == 5) {
        d = rnd.next(1, 100);
        t = rnd.next(500, MAX_DT);
        auto point = pointNearDistance(rnd.next(2, 1414));
        x = point.first;
        y = point.second;
    } else {
        auto point = pointNearDistance(rnd.next(2, 1414));
        x = point.first;
        y = point.second;
        d = rnd.next(1, MAX_DT);
        t = rnd.next(1, MAX_DT);
    }

    println(x, y, d, t);
    return 0;
}
