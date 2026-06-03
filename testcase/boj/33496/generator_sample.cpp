#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

const long long MIN_X = -1000000000LL;
const long long MAX_X = 1000000000LL;
const long long MAX_Y = 1000000000LL;

Point fromLines(long long down, long long up) {
    long long x = (down + up) / 2;
    long long y = (up - down) / 2;
    return {x, y};
}

void addFromLines(vector<Point>& points, long long down, long long up) {
    if ((down + up) % 2 != 0) ++up;
    if (up <= down) up = down + 2;
    Point p = fromLines(down, up);
    if (MIN_X <= p.first && p.first <= MAX_X && 1 <= p.second && p.second <= MAX_Y) {
        points.push_back(p);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        long long x = rnd.next(-10, 10);
        for (int i = 0; i < n; ++i) {
            long long y = rnd.next(1, 20);
            points.push_back({x, y});
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 14);
        long long sharedDown = rnd.next(-20, 10);
        long long sharedUp = rnd.next(-10, 20);
        if ((sharedDown + sharedUp) % 2 != 0) ++sharedUp;
        if (sharedUp <= sharedDown) sharedUp = sharedDown + 2;

        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                long long up = sharedDown + 2 * rnd.next(1, 20);
                addFromLines(points, sharedDown, up);
            } else {
                long long down = sharedUp - 2 * rnd.next(1, 20);
                addFromLines(points, down, sharedUp);
            }
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 16);
        vector<long long> downChoices = {-8, -4, 0, 4, 8};
        vector<long long> upChoices = {2, 6, 10, 14, 18};
        shuffle(downChoices.begin(), downChoices.end());
        shuffle(upChoices.begin(), upChoices.end());

        for (int i = 0; i < n; ++i) {
            long long down = rnd.any(downChoices);
            long long up = rnd.any(upChoices);
            addFromLines(points, down, up);
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 10);
        vector<Point> boundary = {
            {MIN_X, 1},
            {MIN_X, MAX_Y},
            {MAX_X, 1},
            {MAX_X, MAX_Y},
            {0, MAX_Y},
            {-1, 1},
            {1, 1},
        };
        shuffle(boundary.begin(), boundary.end());
        for (int i = 0; i < n; ++i) {
            if (i < (int)boundary.size() && rnd.next(0, 2) != 0) {
                points.push_back(boundary[i]);
            } else {
                points.push_back({rnd.next(-1000000000LL, 1000000000LL), rnd.next(1LL, 1000000000LL)});
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 18);
        long long xBase = rnd.next(-25, 25);
        long long yBase = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            long long x = xBase + rnd.next(-4, 4);
            long long y = max(1LL, yBase + rnd.next(-4, 4));
            points.push_back({x, y});
        }
    } else {
        int n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(-30, 30);
            long long y = rnd.next(1, 30);
            points.push_back({x, y});
        }
    }

    if (points.empty()) {
        points.push_back({0, 1});
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
