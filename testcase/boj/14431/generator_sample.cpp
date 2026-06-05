#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<int, int>;

const int MIN_COORD = -3000;
const int MAX_COORD = 3000;
const int MAX_N = 4000;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

int flooredDistance(Point a, Point b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return static_cast<int>(sqrt(dx * dx + dy * dy));
}

Point randomPoint(int lo = MIN_COORD, int hi = MAX_COORD) {
    return {rnd.next(lo, hi), rnd.next(lo, hi)};
}

Point clampPoint(Point p) {
    p.first = max(MIN_COORD, min(MAX_COORD, p.first));
    p.second = max(MIN_COORD, min(MAX_COORD, p.second));
    return p;
}

Point offset(Point p, int dx, int dy) {
    return clampPoint({p.first + dx, p.second + dy});
}

Point randomNearby(Point base, int radius) {
    return offset(base, rnd.next(-radius, radius), rnd.next(-radius, radius));
}

Point pickEndpointWithPrimeDistance(Point start) {
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    shuffle(primes.begin(), primes.end());
    vector<Point> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    shuffle(dirs.begin(), dirs.end());

    for (int p : primes) {
        for (Point dir : dirs) {
            Point candidate = offset(start, dir.first * p, dir.second * p);
            if (flooredDistance(start, candidate) == p) return candidate;
        }
    }
    return randomPoint(-100, 100);
}

Point pickEndpointWithNonPrimeDistance(Point start) {
    for (int tries = 0; tries < 200; ++tries) {
        Point candidate = randomNearby(start, rnd.next(2, 80));
        if (!isPrime(flooredDistance(start, candidate))) return candidate;
    }
    return offset(start, 4, 0);
}

void printCase(Point start, Point target, vector<Point> waypoints) {
    if (static_cast<int>(waypoints.size()) > MAX_N) waypoints.resize(MAX_N);

    println(start.first, start.second, target.first, target.second);
    println(static_cast<int>(waypoints.size()));
    for (Point p : waypoints) println(p.first, p.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    Point start = randomPoint(-200, 200);
    Point target = randomPoint(-200, 200);
    vector<Point> waypoints;

    if (mode == 0) {
        target = pickEndpointWithPrimeDistance(start);
        int n = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) waypoints.push_back(randomNearby(start, 60));
    } else if (mode == 1) {
        target = pickEndpointWithNonPrimeDistance(start);
        int n = rnd.next(0, 10);
        for (int i = 0; i < n; ++i) waypoints.push_back(randomNearby(start, 70));
    } else if (mode == 2) {
        vector<int> steps = {2, 3, 5, 7, 11, 13, 17};
        int chainLen = rnd.next(1, 8);
        Point cur = start;
        for (int i = 0; i < chainLen; ++i) {
            int step = rnd.any(steps);
            cur = offset(cur, step, 0);
            if (i + 1 < chainLen) waypoints.push_back(cur);
        }
        target = cur;

        int noise = rnd.next(0, 10);
        for (int i = 0; i < noise; ++i) waypoints.push_back(randomNearby(start, 120));
        shuffle(waypoints.begin(), waypoints.end());
    } else if (mode == 3) {
        start = randomPoint(-3000, -2800);
        target = randomPoint(2800, 3000);
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                waypoints.push_back(randomPoint(-3000, 3000));
            } else {
                waypoints.push_back({rnd.next(-3000, 3000), rnd.next(-3000, 3000)});
            }
        }
    } else if (mode == 4) {
        Point center = randomPoint(-50, 50);
        start = center;
        target = randomNearby(center, 4);
        int n = rnd.next(3, 25);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 5) == 0) {
                waypoints.push_back(center);
            } else {
                waypoints.push_back(randomNearby(center, 6));
            }
        }
    } else {
        int n = rnd.next(30, 80);
        for (int i = 0; i < n; ++i) waypoints.push_back(randomPoint(-3000, 3000));
    }

    printCase(start, target, waypoints);
    return 0;
}
