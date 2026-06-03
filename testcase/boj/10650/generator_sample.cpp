#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampCoord(int value) {
    return max(-1000, min(1000, value));
}

pair<int, int> randomPoint(int mode, int index) {
    if (mode == 0) {
        return {rnd.next(-8, 8), rnd.next(-8, 8)};
    }
    if (mode == 1) {
        int base = rnd.next(-20, 20);
        return {clampCoord(base + index * rnd.next(-2, 2)), rnd.next(-12, 12)};
    }
    if (mode == 2) {
        int x = (index % 2 == 0 ? -1000 : 1000);
        int y = rnd.next(-1000, 1000);
        return {x, y};
    }

    int x = rnd.next(-30, 30);
    int y = rnd.next(-30, 30);
    if (index % 3 == 0) x = 0;
    if (index % 4 == 0) y = 0;
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    int q = rnd.next(1, 35);
    int pointMode = rnd.next(0, 3);

    vector<pair<int, int>> checkpoints(n + 1);
    for (int i = 1; i <= n; ++i) {
        checkpoints[i] = randomPoint(pointMode, i);
    }

    println(n, q);
    for (int i = 1; i <= n; ++i) {
        println(checkpoints[i].first, checkpoints[i].second);
    }

    for (int query = 0; query < q; ++query) {
        bool doUpdate = rnd.next(100) < 35;
        if (doUpdate) {
            int i = rnd.next(1, n);
            int updateMode = rnd.next(0, 4);
            pair<int, int> point;
            if (updateMode == 0) {
                point = checkpoints[i];
            } else if (updateMode == 1) {
                point = {rnd.next(-1000, 1000), rnd.next(-1000, 1000)};
            } else {
                int dx = rnd.next(-5, 5);
                int dy = rnd.next(-5, 5);
                point = {clampCoord(checkpoints[i].first + dx),
                         clampCoord(checkpoints[i].second + dy)};
            }
            checkpoints[i] = point;
            println("U", i, point.first, point.second);
        } else {
            int i = rnd.next(1, n);
            int j;
            int spanMode = rnd.next(0, 4);
            if (spanMode == 0) {
                j = i;
            } else if (spanMode == 1) {
                j = min(n, i + rnd.next(0, min(2, n - i)));
            } else {
                j = rnd.next(i, n);
            }
            println("Q", i, j);
        }
    }

    return 0;
}
