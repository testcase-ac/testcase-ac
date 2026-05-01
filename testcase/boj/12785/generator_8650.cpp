#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int w, h, x, y;

    int type = rnd.next(1, 8);

    switch (type) {
        case 1: { // tiny grid, fully random toast
            w = rnd.next(2, 10);
            h = rnd.next(2, 10);
            x = rnd.next(1, w);
            y = rnd.next(1, h);
            break;
        }
        case 2: { // moderate square-ish, toast near center (not on border when possible)
            w = rnd.next(5, 12);
            h = rnd.next(5, 12);
            int lx = max(2, w / 3);
            int rx = min(w - 1, w - w / 3);
            int ly = max(2, h / 3);
            int ry = min(h - 1, h - h / 3);
            if (lx > rx) { lx = 2; rx = w - 1; }
            if (ly > ry) { ly = 2; ry = h - 1; }
            x = rnd.next(lx, rx);
            y = rnd.next(ly, ry);
            break;
        }
        case 3: { // line-like grids (one dimension = 2)
            if (rnd.next(0, 1) == 0) {
                w = rnd.next(2, 15);
                h = 2;
            } else {
                w = 2;
                h = rnd.next(2, 15);
            }
            x = rnd.next(1, w);
            y = rnd.next(1, h);
            break;
        }
        case 4: { // toast at home
            w = rnd.next(2, 15);
            h = rnd.next(2, 15);
            x = 1;
            y = 1;
            break;
        }
        case 5: { // toast at school
            w = rnd.next(2, 15);
            h = rnd.next(2, 15);
            x = w;
            y = h;
            break;
        }
        case 6: { // toast on left/right border (not corners)
            w = rnd.next(3, 15);
            h = rnd.next(3, 15);
            y = rnd.next(2, h - 1);
            if (rnd.next(0, 1) == 0)
                x = 1;
            else
                x = w;
            break;
        }
        case 7: { // toast on bottom/top border (not corners)
            w = rnd.next(3, 15);
            h = rnd.next(3, 15);
            x = rnd.next(2, w - 1);
            if (rnd.next(0, 1) == 0)
                y = 1;
            else
                y = h;
            break;
        }
        case 8: default: { // larger grid, fully random but kept small for validator
            w = rnd.next(15, 30);
            h = rnd.next(15, 30);
            x = rnd.next(1, w);
            y = rnd.next(1, h);
            break;
        }
    }

    println(w, h);
    println(x, y);

    return 0;
}
