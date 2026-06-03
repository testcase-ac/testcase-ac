#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampCoord(int v) {
    return max(-300, min(300, v));
}

pair<int, int> pickNearRinkPoint(int w, int h, int x, int y) {
    int r = h / 2;
    int mode = rnd.next(0, 8);

    if (mode == 0) {
        return {rnd.next(x, x + w), rnd.next(y, y + h)};
    }
    if (mode == 1) {
        return {x + rnd.next(0, w), y + rnd.any(vector<int>{0, h})};
    }
    if (mode == 2) {
        return {x + rnd.any(vector<int>{0, w}), y + rnd.next(0, h)};
    }
    if (mode == 3) {
        int dx = rnd.next(-r, r);
        int dy = rnd.next(-r, r);
        return {x + dx, y + r + dy};
    }
    if (mode == 4) {
        int dx = rnd.next(-r, r);
        int dy = rnd.next(-r, r);
        return {x + w + dx, y + r + dy};
    }
    if (mode == 5) {
        return {x - r - rnd.next(0, 3), y + r + rnd.next(-r - 3, r + 3)};
    }
    if (mode == 6) {
        return {x + w + r + rnd.next(0, 3), y + r + rnd.next(-r - 3, r + 3)};
    }
    if (mode == 7) {
        return {rnd.next(-300, 300), rnd.next(-300, 300)};
    }

    vector<pair<int, int>> anchors = {
        {x, y}, {x, y + h}, {x + w, y}, {x + w, y + h},
        {x - r, y + r}, {x + w + r, y + r},
        {x - r - 1, y + r}, {x + w + r + 1, y + r},
    };
    return rnd.any(anchors);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int w, h, x, y;
    int rinkMode = rnd.next(0, 4);
    if (rinkMode == 0) {
        w = rnd.next(1, 12);
        h = 2 * rnd.next(1, 6);
        x = rnd.next(-20, 20);
        y = rnd.next(-20, 20);
    } else if (rinkMode == 1) {
        w = rnd.next(70, 100);
        h = 2 * rnd.next(35, 50);
        x = rnd.next(-100, -50);
        y = rnd.next(50, 100);
    } else if (rinkMode == 2) {
        w = rnd.next(1, 100);
        h = 2 * rnd.next(1, 50);
        x = rnd.any(vector<int>{-100, 100 - w, rnd.next(-100, 100)});
        y = rnd.any(vector<int>{-100, 100 - h, rnd.next(-100, 100)});
    } else {
        w = rnd.next(1, 100);
        h = 2 * rnd.next(1, 50);
        x = rnd.next(-100, 100);
        y = rnd.next(-100, 100);
    }

    int p = rnd.next(1, 50);
    vector<pair<int, int>> players;
    for (int i = 0; i < p; ++i) {
        auto point = pickNearRinkPoint(w, h, x, y);
        players.push_back({clampCoord(point.first), clampCoord(point.second)});
    }

    println(w, h, x, y, p);
    for (auto player : players) {
        println(player.first, player.second);
    }

    return 0;
}
