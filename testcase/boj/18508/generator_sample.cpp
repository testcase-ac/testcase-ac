#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    set<Point> used;

    int rows = rnd.next(1, 4);
    int baseY = rnd.next(0, 40);
    if (rnd.next(5) == 0) {
        baseY = rnd.next(999999850, 999999920);
    }
    int rowGap = rnd.next(8, 20);

    for (int r = 0; r < rows; ++r) {
        int pairs = rnd.next(1, 4);
        int y = baseY + r * rowGap;
        int x = rnd.next(0, 40);
        if (rnd.next(5) == 0) {
            x = rnd.next(999999850, 999999920);
        }

        for (int i = 0; i < pairs; ++i) {
            int width = rnd.next(1, 4);
            Point a = {x, y};
            Point b = {x + width, y};
            if (used.insert(a).second) {
                points.push_back(a);
            }
            if (used.insert(b).second) {
                points.push_back(b);
            }
            x += width + rnd.next(5, 15);
        }
    }

    shuffle(points.begin(), points.end());

    println((int)points.size());
    for (Point p : points) {
        println(p.first, p.second);
    }

    return 0;
}
