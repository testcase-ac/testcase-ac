#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long MIN_COORD = -100000000LL;
const long long MAX_COORD = 100000000LL;

long long clampCoord(long long value) {
    return max(MIN_COORD, min(MAX_COORD, value));
}

Point addDelta(Point p, long long dx, long long dy) {
    return {clampCoord(p.first + dx), clampCoord(p.second + dy)};
}

Point randomPoint(long long lo, long long hi) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<Point> students;
    vector<Point> tutors;

    if (mode == 0) {
        n = rnd.next(1, 8);
        Point shared = randomPoint(-20, 20);
        long long spread = rnd.next(0, 6);
        for (int i = 0; i < n; ++i) {
            students.push_back(rnd.next(0, 2) == 0 ? shared : randomPoint(-spread, spread));
            tutors.push_back(rnd.next(0, 2) == 0 ? shared : randomPoint(-spread, spread));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        long long base = rnd.next(-30, 30);
        long long gap = rnd.next(1, 7);
        long long shift = rnd.next(-8, 8);
        for (int i = 0; i < n; ++i) {
            students.push_back({base + i * gap, rnd.next(-3, 3)});
            tutors.push_back({base + (n - 1 - i) * gap + shift, rnd.next(-3, 3)});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        Point centerA = randomPoint(-50, 50);
        Point centerB = addDelta(centerA, rnd.next(-25, 25), rnd.next(-25, 25));
        long long radius = rnd.next(0, 12);
        for (int i = 0; i < n; ++i) {
            students.push_back(addDelta(centerA, rnd.next(-radius, radius), rnd.next(-radius, radius)));
            tutors.push_back(addDelta(centerB, rnd.next(-radius, radius), rnd.next(-radius, radius)));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        vector<Point> corners = {
            {MIN_COORD, MIN_COORD},
            {MIN_COORD, MAX_COORD},
            {MAX_COORD, MIN_COORD},
            {MAX_COORD, MAX_COORD},
            {0, 0},
        };
        for (int i = 0; i < n; ++i) {
            Point s = rnd.any(corners);
            Point t = rnd.any(corners);
            students.push_back(addDelta(s, rnd.next(-3, 3), rnd.next(-3, 3)));
            tutors.push_back(addDelta(t, rnd.next(-3, 3), rnd.next(-3, 3)));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 14);
        long long offsetX = rnd.next(-10, 10);
        long long offsetY = rnd.next(-10, 10);
        for (int i = 0; i < n; ++i) {
            Point p = randomPoint(-40, 40);
            students.push_back(p);
            tutors.push_back(addDelta(p, offsetX + rnd.next(-2, 2), offsetY + rnd.next(-2, 2)));
        }
        shuffle(tutors.begin(), tutors.end());
    } else {
        n = rnd.next(1, 20);
        long long span = rnd.any(vector<long long>{5, 20, 100, 1000});
        for (int i = 0; i < n; ++i) {
            students.push_back(randomPoint(-span, span));
            tutors.push_back(randomPoint(-span, span));
        }
    }

    println(n);
    for (const Point& p : students) {
        println(p.first, p.second);
    }
    for (const Point& p : tutors) {
        println(p.first, p.second);
    }

    return 0;
}
