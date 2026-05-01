#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> types = {0,1,2,3,4,5,6,7,8,9,10};
    int T = rnd.next(5, 12);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int kind = rnd.any(types);
        int rect_minx, rect_maxx, rect_miny, rect_maxy;
        int sx1, sy1, sx2, sy2;
        if (kind == 0) {
            // inside: segment fully inside non-degenerate rectangle
            do {
                int x1 = rnd.next(-30, 30), x2 = rnd.next(-30, 30);
                rect_minx = min(x1, x2);
                rect_maxx = max(x1, x2);
            } while (rect_maxx - rect_minx < 2);
            do {
                int y1 = rnd.next(-30, 30), y2 = rnd.next(-30, 30);
                rect_miny = min(y1, y2);
                rect_maxy = max(y1, y2);
            } while (rect_maxy - rect_miny < 2);
            sx1 = rnd.next(rect_minx + 1, rect_maxx - 1);
            sy1 = rnd.next(rect_miny + 1, rect_maxy - 1);
            sx2 = rnd.next(rect_minx + 1, rect_maxx - 1);
            sy2 = rnd.next(rect_miny + 1, rect_maxy - 1);
        }
        else if (kind == 1) {
            // outside_no: segment completely outside, no intersection
            do {
                int x1 = rnd.next(-30, 30), x2 = rnd.next(-30, 30);
                rect_minx = min(x1, x2);
                rect_maxx = max(x1, x2);
            } while (rect_maxx - rect_minx < 1);
            do {
                int y1 = rnd.next(-30, 30), y2 = rnd.next(-30, 30);
                rect_miny = min(y1, y2);
                rect_maxy = max(y1, y2);
            } while (rect_maxy - rect_miny < 1);
            int d = rnd.next(0, 3);
            if (d == 0) {
                sx1 = rnd.next(-50, rect_minx - 1); sy1 = rnd.next(-50, 50);
                sx2 = rnd.next(-50, rect_minx - 1); sy2 = rnd.next(-50, 50);
            } else if (d == 1) {
                sx1 = rnd.next(rect_maxx + 1, 50); sy1 = rnd.next(-50, 50);
                sx2 = rnd.next(rect_maxx + 1, 50); sy2 = rnd.next(-50, 50);
            } else if (d == 2) {
                sx1 = rnd.next(-50, 50); sy1 = rnd.next(rect_maxy + 1, 50);
                sx2 = rnd.next(-50, 50); sy2 = rnd.next(rect_maxy + 1, 50);
            } else {
                sx1 = rnd.next(-50, 50); sy1 = rnd.next(-50, rect_miny - 1);
                sx2 = rnd.next(-50, 50); sy2 = rnd.next(-50, rect_miny - 1);
            }
        }
        else if (kind == 2) {
            // cross: one endpoint left, one right
            do {
                int x1 = rnd.next(-30, 30), x2 = rnd.next(-30, 30);
                rect_minx = min(x1, x2);
                rect_maxx = max(x1, x2);
            } while (rect_maxx - rect_minx < 1);
            do {
                int y1 = rnd.next(-30, 30), y2 = rnd.next(-30, 30);
                rect_miny = min(y1, y2);
                rect_maxy = max(y1, y2);
            } while (rect_maxy - rect_miny < 1);
            sy1 = rnd.next(rect_miny, rect_maxy);
            sy2 = rnd.next(rect_miny, rect_maxy);
            sx1 = rnd.next(-50, rect_minx - 1);
            sx2 = rnd.next(rect_maxx + 1, 50);
        }
        else if (kind == 3) {
            // touch_edge
            do {
                int x1 = rnd.next(-30, 30), x2 = rnd.next(-30, 30);
                rect_minx = min(x1, x2);
                rect_maxx = max(x1, x2);
            } while (rect_maxx - rect_minx < 1);
            do {
                int y1 = rnd.next(-30, 30), y2 = rnd.next(-30, 30);
                rect_miny = min(y1, y2);
                rect_maxy = max(y1, y2);
            } while (rect_maxy - rect_miny < 1);
            int e = rnd.next(0,3);
            if (e == 0) {
                sy1 = sy2 = rect_miny;
                sx1 = rnd.next(-50, rect_minx - 1);
                sx2 = rnd.next(rect_maxx + 1, 50);
            } else if (e == 1) {
                sy1 = sy2 = rect_maxy;
                sx1 = rnd.next(-50, rect_minx - 1);
                sx2 = rnd.next(rect_maxx + 1, 50);
            } else if (e == 2) {
                sx1 = sx2 = rect_minx;
                sy1 = rnd.next(-50, rect_miny - 1);
                sy2 = rnd.next(rect_maxy + 1, 50);
            } else {
                sx1 = sx2 = rect_maxx;
                sy1 = rnd.next(-50, rect_miny - 1);
                sy2 = rnd.next(rect_maxy + 1, 50);
            }
        }
        else if (kind == 4) {
            // touch_corner
            do {
                int x1 = rnd.next(-30, 30), x2 = rnd.next(-30, 30);
                rect_minx = min(x1, x2);
                rect_maxx = max(x1, x2);
            } while (rect_maxx - rect_minx < 1);
            do {
                int y1 = rnd.next(-30, 30), y2 = rnd.next(-30, 30);
                rect_miny = min(y1, y2);
                rect_maxy = max(y1, y2);
            } while (rect_maxy - rect_miny < 1);
            int c = rnd.next(0,3);
            if (c == 0) {
                sx1 = rect_minx; sy1 = rect_miny;
                sx2 = rect_minx - 1; sy2 = rect_miny - 1;
            } else if (c == 1) {
                sx1 = rect_minx; sy1 = rect_maxy;
                sx2 = rect_minx - 1; sy2 = rect_maxy + 1;
            } else if (c == 2) {
                sx1 = rect_maxx; sy1 = rect_miny;
                sx2 = rect_maxx + 1; sy2 = rect_miny - 1;
            } else {
                sx1 = rect_maxx; sy1 = rect_maxy;
                sx2 = rect_maxx + 1; sy2 = rect_maxy + 1;
            }
        }
        else if (kind == 5) {
            // rect_line_horiz_int
            int y = rnd.next(-40, 40), a, b;
            do {
                a = rnd.next(-30, 30); b = rnd.next(-30, 30);
                rect_minx = min(a, b);
                rect_maxx = max(a, b);
            } while (rect_maxx - rect_minx < 1);
            rect_miny = rect_maxy = y;
            sx1 = rect_minx - 1; sy1 = y;
            sx2 = rect_maxx + 1; sy2 = y;
        }
        else if (kind == 6) {
            // rect_line_horiz_no
            int y = rnd.next(-40, 40), a, b;
            do {
                a = rnd.next(-30, 30); b = rnd.next(-30, 30);
                rect_minx = min(a, b);
                rect_maxx = max(a, b);
            } while (rect_maxx - rect_minx < 1);
            rect_miny = rect_maxy = y;
            int dir = rnd.next(0,1);
            int sy = dir ? y + 1 : y - 1;
            sx1 = rnd.next(-50, 50); sy1 = sy;
            sx2 = rnd.next(-50, 50); sy2 = sy;
        }
        else if (kind == 7) {
            // rect_line_vert_int
            int x = rnd.next(-40, 40), a, b;
            do {
                a = rnd.next(-30, 30); b = rnd.next(-30, 30);
                rect_miny = min(a, b);
                rect_maxy = max(a, b);
            } while (rect_maxy - rect_miny < 1);
            rect_minx = rect_maxx = x;
            sx1 = x; sy1 = rect_miny - 1;
            sx2 = x; sy2 = rect_maxy + 1;
        }
        else if (kind == 8) {
            // rect_line_vert_no
            int x = rnd.next(-40, 40), a, b;
            do {
                a = rnd.next(-30, 30); b = rnd.next(-30, 30);
                rect_miny = min(a, b);
                rect_maxy = max(a, b);
            } while (rect_maxy - rect_miny < 1);
            rect_minx = rect_maxx = x;
            int dir = rnd.next(0,1);
            int sx = dir ? x + 1 : x - 1;
            sx1 = sx; sy1 = rnd.next(-50, 50);
            sx2 = sx; sy2 = rnd.next(-50, 50);
        }
        else if (kind == 9) {
            // rect_point_int
            int x = rnd.next(-40, 40), y = rnd.next(-40, 40);
            rect_minx = rect_maxx = x;
            rect_miny = rect_maxy = y;
            sx1 = x; sy1 = y;
            do {
                sx2 = rnd.next(-50, 50);
                sy2 = rnd.next(-50, 50);
            } while (sx2 == x && sy2 == y);
        }
        else {
            // rect_point_no
            int x = rnd.next(-40, 40), y = rnd.next(-40, 40);
            rect_minx = rect_maxx = x;
            rect_miny = rect_maxy = y;
            sx1 = x + 1; sy1 = y + 1;
            sx2 = x + 2; sy2 = y + 2;
        }
        int rx1 = rect_minx, ry1 = rect_maxy;
        int rx2 = rect_maxx, ry2 = rect_miny;
        if (rnd.next(0,1)) swap(rx1, rx2);
        if (rnd.next(0,1)) swap(ry1, ry2);
        printf("%d %d %d %d %d %d %d %d\n", sx1, sy1, sx2, sy2, rx1, ry1, rx2, ry2);
    }
    return 0;
}
