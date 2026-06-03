#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

using Point = pair<int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Point> points;
    int mode = rnd.next(6);

    if (mode == 0) {
        int n = rnd.next(1, 8);
        int x = rnd.next(-1000, 1000);
        int y = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(3) == 0) {
                points.push_back({x, y});
            } else {
                points.push_back({rnd.next(-1000, 1000), rnd.next(-1000, 1000)});
            }
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 30);
        bool vertical = rnd.next(2);
        int fixed = rnd.next(-1000, 1000);
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(-1000, 1000);
            points.push_back(vertical ? Point{fixed, t} : Point{t, fixed});
        }
    } else if (mode == 2) {
        int x1 = rnd.next(-1000, 500);
        int y1 = rnd.next(-1000, 500);
        int x2 = rnd.next(x1 + 1, 1000);
        int y2 = rnd.next(y1 + 1, 1000);
        points = {{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}};
        int extra = rnd.next(0, 16);
        for (int i = 0; i < extra; ++i) {
            points.push_back({rnd.next(x1, x2), rnd.next(y1, y2)});
        }
    } else if (mode == 3) {
        int n = rnd.next(3, 45);
        int loX = rnd.next(-1000, 800);
        int hiX = rnd.next(loX, 1000);
        int loY = rnd.next(-1000, 800);
        int hiY = rnd.next(loY, 1000);
        for (int i = 0; i < n; ++i) {
            points.push_back({rnd.next(loX, hiX), rnd.next(loY, hiY)});
        }
    } else if (mode == 4) {
        points = {{-1000, -1000}, {-1000, 1000}, {1000, -1000}, {1000, 1000}};
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) {
            int side = rnd.next(4);
            int t = rnd.next(-1000, 1000);
            if (side == 0) points.push_back({-1000, t});
            if (side == 1) points.push_back({1000, t});
            if (side == 2) points.push_back({t, -1000});
            if (side == 3) points.push_back({t, 1000});
        }
    } else {
        int n = rnd.next(3, 36);
        int ax = rnd.next(-900, 0);
        int ay = rnd.next(-900, 0);
        int bx = rnd.next(0, 900);
        int by = rnd.next(-900, 0);
        int cx = rnd.next(-900, 900);
        int cy = rnd.next(0, 900);
        points = {{ax, ay}, {bx, by}, {cx, cy}};
        while ((int)points.size() < n) {
            int u = rnd.next(0, 100);
            int v = rnd.next(0, 100 - u);
            int w = 100 - u - v;
            int x = (u * ax + v * bx + w * cx) / 100;
            int y = (u * ay + v * by + w * cy) / 100;
            points.push_back({x, y});
        }
    }

    shuffle(points.begin(), points.end());
    println((int)points.size());
    for (const Point& p : points) {
        println(p.first, p.second);
    }

    return 0;
}
