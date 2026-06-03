#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int W, H;
    if (mode == 0) {
        W = rnd.next(1, 3);
        H = rnd.next(1, 3);
    } else if (mode == 1) {
        W = rnd.next(25, 30);
        H = rnd.next(25, 30);
    } else if (mode == 2) {
        int widths[] = {1, 2, 30};
        W = widths[rnd.next(0, 2)];
        H = rnd.next(1, 30);
    } else if (mode == 3) {
        W = rnd.next(1, 30);
        int heights[] = {1, 2, 30};
        H = heights[rnd.next(0, 2)];
    } else {
        W = rnd.next(1, 30);
        H = rnd.next(1, 30);
    }

    int y = rnd.next(0, H);
    int y1;
    if (rnd.next(0, 2) == 0) {
        if (y == 0)
            y1 = rnd.next(1, H);
        else if (y == H)
            y1 = rnd.next(0, H - 1);
        else
            y1 = rnd.next(0, 1) == 0 ? rnd.next(0, y - 1) : rnd.next(y + 1, H);
    } else {
        if (rnd.next(0, 1) == 0 && y != 0)
            y1 = 0;
        else if (y != H)
            y1 = H;
        else
            y1 = rnd.next(0, H - 1);
    }

    int x;
    if (rnd.next(0, 3) == 0)
        x = rnd.next(0, 1) == 0 ? 0 : W;
    else
        x = rnd.next(0, W);

    int x1, x2;
    if (mode == 4 && W >= 2) {
        x1 = rnd.next(0, W - 2);
        x2 = x1 + 1;
    } else if (mode == 5) {
        x1 = 0;
        x2 = W;
    } else {
        x1 = rnd.next(0, W - 1);
        x2 = rnd.next(x1 + 1, W);
    }

    println(W, H);
    println(x, y);
    println(x1, y1, x2, y1);

    return 0;
}
