#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<long long, long long>;

static vector<Point> makeParabolaPoints(int count) {
    int stepX = rnd.next(1, 7);
    int scaleY = rnd.next(1, 5);
    if (rnd.next(0, 1) == 0) {
        scaleY = -scaleY;
    }

    int start = rnd.next(-40, 40);
    long long offsetX = rnd.next(-200, 200);
    long long offsetY = rnd.next(-500, 500);

    vector<Point> points;
    points.reserve(count);
    for (int i = 0; i < count; ++i) {
        long long baseX = start + i;
        long long x = offsetX + stepX * baseX;
        long long y = offsetY + scaleY * baseX * baseX;
        points.push_back({x, y});
    }

    shuffle(points.begin(), points.end());
    return points;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(0, 3) == 0) {
            n = 1;
        } else {
            n = rnd.next(1, 8);
        }

        println(n);
        vector<Point> points = makeParabolaPoints(3 * n);
        for (const Point& point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}
