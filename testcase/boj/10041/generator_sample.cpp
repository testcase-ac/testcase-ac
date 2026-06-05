#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomPoint(int w, int h) {
    return {rnd.next(1, w), rnd.next(1, h)};
}

pair<int, int> clampPoint(int x, int y, int w, int h) {
    x = max(1, min(w, x));
    y = max(1, min(h, y));
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w, h, n;
    vector<pair<int, int>> points;

    if (mode == 0) {
        w = rnd.next(2, 8);
        h = rnd.next(2, 8);
        n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) points.push_back(randomPoint(w, h));
    } else if (mode == 1) {
        w = rnd.next(4, 30);
        h = rnd.next(4, 30);
        n = rnd.next(4, 18);
        int x = rnd.next(1, w);
        int y = rnd.next(1, h);
        int sx = rnd.any(vector<int>{-1, 1});
        int sy = sx;
        for (int i = 0; i < n; ++i) {
            points.push_back(clampPoint(x, y, w, h));
            x += sx * rnd.next(1, 4);
            y += sy * rnd.next(1, 4);
            if (x < 1 || x > w) sx *= -1;
            if (y < 1 || y > h) sy *= -1;
            x = max(1, min(w, x));
            y = max(1, min(h, y));
        }
    } else if (mode == 2) {
        w = rnd.next(5, 60);
        h = rnd.next(5, 60);
        n = rnd.next(5, 16);
        vector<pair<int, int>> corners = {{1, 1}, {1, h}, {w, 1}, {w, h}};
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                points.push_back(rnd.any(corners));
            } else {
                int side = rnd.next(0, 3);
                if (side == 0) points.push_back({1, rnd.next(1, h)});
                if (side == 1) points.push_back({w, rnd.next(1, h)});
                if (side == 2) points.push_back({rnd.next(1, w), 1});
                if (side == 3) points.push_back({rnd.next(1, w), h});
            }
        }
    } else if (mode == 3) {
        w = rnd.next(2, 100);
        h = rnd.next(2, 100);
        n = rnd.next(6, 20);
        auto a = randomPoint(w, h);
        auto b = randomPoint(w, h);
        while (b == a) b = randomPoint(w, h);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                points.push_back(randomPoint(w, h));
            } else {
                points.push_back((i % 2 == 0) ? a : b);
            }
        }
    } else if (mode == 4) {
        w = rnd.next(1000, 10000);
        h = rnd.next(1000, 10000);
        n = rnd.next(3, 12);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) points.push_back({rnd.next(1, 30), rnd.next(1, 30)});
            else if (i % 3 == 1) points.push_back({w - rnd.next(0, 29), h - rnd.next(0, 29)});
            else points.push_back(randomPoint(w, h));
        }
    } else {
        w = rnd.next(3, 40);
        h = rnd.next(3, 40);
        n = rnd.next(5, 18);
        int x = rnd.next(1, w);
        int y = rnd.next(1, h);
        for (int i = 0; i < n; ++i) {
            points.push_back({x, y});
            int dx = rnd.next(-5, 5);
            int dy = rnd.next(-5, 5);
            if (rnd.next(0, 3) == 0) dy = -dx;
            x = max(1, min(w, x + dx));
            y = max(1, min(h, y + dy));
        }
    }

    println(w, h, (int)points.size());
    for (auto point : points) println(point.first, point.second);

    return 0;
}
