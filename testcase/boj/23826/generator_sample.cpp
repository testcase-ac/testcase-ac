#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
};

int clampCoord(int v) {
    return max(0, min(1000, v));
}

Point jitter(Point base, int radius) {
    return {clampCoord(base.x + rnd.next(-radius, radius)),
            clampCoord(base.y + rnd.next(-radius, radius))};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 0 ? 30 : 15);

    Point source{rnd.next(0, 1000), rnd.next(0, 1000)};
    int e0 = rnd.next(1, 2000);
    vector<Point> rooms(n);
    vector<int> energy(n);

    if (mode == 0) {
        Point center{rnd.next(0, 1000), rnd.next(0, 1000)};
        int radius = rnd.next(0, 8);
        source = jitter(center, radius);
        e0 = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            rooms[i] = jitter(center, radius);
            energy[i] = rnd.next(0, 40);
        }
    } else if (mode == 1) {
        int y = rnd.next(0, 1000);
        int step = rnd.next(1, 80);
        int start = rnd.next(0, 1000);
        source = {start, y};
        e0 = rnd.next(1, 500);
        for (int i = 0; i < n; ++i) {
            rooms[i] = {clampCoord(start + (i + 1) * step), y};
            energy[i] = rnd.next(0, 250);
        }
        shuffle(rooms.begin(), rooms.end());
    } else if (mode == 2) {
        vector<Point> corners{{0, 0}, {0, 1000}, {1000, 0}, {1000, 1000}};
        source = rnd.any(corners);
        e0 = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            rooms[i] = rnd.next(0, 1) ? rnd.any(corners) : jitter(rnd.any(corners), rnd.next(0, 5));
            energy[i] = rnd.next(0, 1000);
        }
    } else if (mode == 3) {
        Point p{rnd.next(0, 1000), rnd.next(0, 1000)};
        source = p;
        e0 = rnd.next(1, 1200);
        for (int i = 0; i < n; ++i) {
            rooms[i] = rnd.next(0, 3) == 0 ? jitter(p, rnd.next(1, 4)) : p;
            energy[i] = rnd.next(0, 1000);
        }
    } else if (mode == 4) {
        source = {rnd.next(0, 40), rnd.next(0, 40)};
        e0 = rnd.next(1, 120);
        for (int i = 0; i < n; ++i) {
            rooms[i] = {rnd.next(900, 1000), rnd.next(900, 1000)};
            energy[i] = rnd.next(0, 1000);
        }
    } else {
        e0 = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) {
            rooms[i] = {rnd.next(0, 1000), rnd.next(0, 1000)};
            energy[i] = rnd.next(0, 1000);
        }
    }

    println(n);
    println(source.x, source.y, e0);
    for (int i = 0; i < n; ++i) {
        println(rooms[i].x, rooms[i].y, energy[i]);
    }

    return 0;
}
