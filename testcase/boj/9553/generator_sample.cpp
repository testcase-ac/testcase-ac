#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Segment {
    int x1;
    int y1;
    int x2;
    int y2;
};

long long cross(long long ax, long long ay, long long bx, long long by) {
    return ax * by - ay * bx;
}

bool containsOrigin(const Segment& s) {
    if (cross(s.x1, s.y1, s.x2, s.y2) != 0) {
        return false;
    }
    return min(s.x1, s.x2) <= 0 && 0 <= max(s.x1, s.x2) &&
           min(s.y1, s.y2) <= 0 && 0 <= max(s.y1, s.y2);
}

int nonZeroCoord() {
    int v = rnd.next(-100, 100);
    while (v == 0) {
        v = rnd.next(-100, 100);
    }
    return v;
}

int nearCoord(int center, int radius) {
    return max(-100, min(100, center + rnd.next(-radius, radius)));
}

Segment randomSegment() {
    Segment s;
    do {
        int mode = rnd.next(7);
        if (mode == 0) {
            s = {nonZeroCoord(), nonZeroCoord(), nonZeroCoord(), nonZeroCoord()};
        } else if (mode == 1) {
            int x = nonZeroCoord();
            s = {x, rnd.next(-100, 100), x, rnd.next(-100, 100)};
        } else if (mode == 2) {
            int y = nonZeroCoord();
            s = {rnd.next(-100, 100), y, rnd.next(-100, 100), y};
        } else if (mode == 3) {
            int x = rnd.any(vector<int>{-100, -99, 99, 100});
            int y = rnd.any(vector<int>{-100, -99, 99, 100});
            s = {x, rnd.next(-100, 100), rnd.next(-100, 100), y};
        } else if (mode == 4) {
            int cx = nonZeroCoord();
            int cy = nonZeroCoord();
            s = {nearCoord(cx, 8), nearCoord(cy, 8), nearCoord(cx, 8), nearCoord(cy, 8)};
        } else if (mode == 5) {
            int x = nonZeroCoord();
            int y = nonZeroCoord();
            s = {x, y, x, y};
        } else {
            s = {rnd.next(-100, 100), rnd.next(-100, 100),
                 rnd.next(-100, 100), rnd.next(-100, 100)};
        }
    } while (containsOrigin(s));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(1, 18);
        if (rnd.next(5) == 0) {
            n = rnd.next(40, 100);
        }

        vector<Segment> targets;
        targets.reserve(n);

        if (rnd.next(4) == 0) {
            Segment base = randomSegment();
            int copies = min(n, rnd.next(2, 8));
            for (int i = 0; i < copies; ++i) {
                Segment s = base;
                if (rnd.next(2) == 0) {
                    swap(s.x1, s.x2);
                    swap(s.y1, s.y2);
                }
                targets.push_back(s);
            }
        }

        while ((int)targets.size() < n) {
            targets.push_back(randomSegment());
        }

        shuffle(targets.begin(), targets.end());
        println(n);
        for (const Segment& s : targets) {
            println(s.x1, s.y1, s.x2, s.y2);
        }
    }

    return 0;
}
