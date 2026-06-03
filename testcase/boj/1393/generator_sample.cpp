#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int bounded(int value) {
    return max(-100, min(100, value));
}

pair<int, int> makePointNear(int x, int y, int radius) {
    for (int attempt = 0; attempt < 100; ++attempt) {
        int nx = x + rnd.next(-radius, radius);
        int ny = y + rnd.next(-radius, radius);
        if (-100 <= nx && nx <= 100 && -100 <= ny && ny <= 100) {
            return {nx, ny};
        }
    }
    return {bounded(x), bounded(y)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> dirs = {
        {0, 0},   {1, 0},   {-1, 0},  {0, 1},  {0, -1},
        {1, 1},   {1, -1},  {-1, 1},  {-1, -1},
        {1, 2},   {2, 1},   {-1, 2},  {2, -1},
        {3, 2},   {-2, 3},  {3, -2},  {-3, -2},
    };

    int mode = rnd.next(0, 5);
    pair<int, int> step = rnd.any(dirs);
    if (mode == 0) {
        step = {0, 0};
    } else if (mode == 1) {
        step = rnd.any(vector<pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}});
    } else if (mode == 2) {
        step = rnd.any(vector<pair<int, int>>{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
    }

    int scale = step == pair<int, int>{0, 0} ? 0 : rnd.next(1, 8);
    int dx = step.first * scale;
    int dy = step.second * scale;

    int xe = rnd.next(-30, 30);
    int ye = rnd.next(-30, 30);
    int xs = rnd.next(-40, 40);
    int ys = rnd.next(-40, 40);

    if (mode == 3 && step != pair<int, int>{0, 0}) {
        int t = rnd.next(0, 12);
        xs = xe + step.first * t;
        ys = ye + step.second * t;
        auto p = makePointNear(xs, ys, rnd.next(0, 3));
        xs = p.first;
        ys = p.second;
    } else if (mode == 4 && step != pair<int, int>{0, 0}) {
        int t = rnd.next(-12, -1);
        xs = xe + step.first * t + rnd.next(-2, 2);
        ys = ye + step.second * t + rnd.next(-2, 2);
    } else if (mode == 5) {
        xs = xe;
        ys = ye;
    }

    println(bounded(xs), bounded(ys));
    println(bounded(xe), bounded(ye), bounded(dx), bounded(dy));

    return 0;
}
