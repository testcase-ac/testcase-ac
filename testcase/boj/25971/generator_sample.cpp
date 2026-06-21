#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

struct Observation {
    int day;
    Point p;
};

Point add(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

Point mul(Point a, long long scale) {
    return {a.x * scale, a.y * scale};
}

Point leftOf(Point dir) {
    return {-dir.y, dir.x};
}

Point rightOf(Point dir) {
    return {dir.y, -dir.x};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 30);
    int k = rnd.next(3, min(n, 9));
    long long r = rnd.next(1, 8);
    int q = rnd.next(8, 24);

    vector<int> days;
    days.push_back(1);
    for (int day = 2; day < n; ++day) {
        days.push_back(day);
    }
    shuffle(days.begin() + 1, days.end());
    days.resize(k - 1);
    days.push_back(n);
    sort(days.begin(), days.end());

    vector<Point> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    Point current = {rnd.next(-10, 10), rnd.next(-10, 10)};
    vector<Observation> observations;
    observations.push_back({days[0], current});

    for (int idx = 1; idx < k; ++idx) {
        Point dir = rnd.any(directions);
        int dt = days[idx] - days[idx - 1];
        current = add(current, mul(dir, dt));
        observations.push_back({days[idx], current});
    }

    println(n, k, r, q);
    for (const Observation& observation : observations) {
        println(observation.day, observation.p.x, observation.p.y);
    }

    for (int query = 0; query < q; ++query) {
        int seg = rnd.next(0, k - 1);
        int day;
        if (seg == k - 1) {
            day = n;
        } else {
            day = rnd.next(observations[seg].day, observations[seg + 1].day - 1);
        }

        Point dir;
        if (seg == k - 1) {
            Point prev = observations[k - 2].p;
            Point now = observations[k - 1].p;
            dir = {(now.x - prev.x) / (observations[k - 1].day - observations[k - 2].day),
                   (now.y - prev.y) / (observations[k - 1].day - observations[k - 2].day)};
        } else {
            Point now = observations[seg].p;
            Point next = observations[seg + 1].p;
            dir = {(next.x - now.x) / (observations[seg + 1].day - observations[seg].day),
                   (next.y - now.y) / (observations[seg + 1].day - observations[seg].day)};
        }

        Point center = add(observations[seg].p, mul(dir, day - observations[seg].day));
        int mode = rnd.next(0, 5);
        Point person = center;
        if (mode == 0) {
            person = add(center, mul(leftOf(dir), rnd.next(1, (int)r)));
        } else if (mode == 1) {
            person = add(center, mul(rightOf(dir), rnd.next(1, (int)r)));
        } else if (mode == 2) {
            person = center;
        } else if (mode == 3) {
            person = add(center, mul(leftOf(dir), r + rnd.next(1, 4)));
        } else if (mode == 4) {
            person = add(add(center, mul(leftOf(dir), rnd.next(1, (int)r))),
                         mul(dir, rnd.next(-2, 2)));
        } else {
            person = {rnd.next(-15, 15), rnd.next(-15, 15)};
        }

        println(day, person.x, person.y);
    }

    return 0;
}
