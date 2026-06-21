#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int b = 1;
    int w = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        b = rnd.next(1, 5);
        w = rnd.next(1, 5);
    } else if (mode == 1) {
        b = rnd.next(1, 20);
        w = rnd.next(1, 1000);
        if (rnd.next(0, 1)) {
            int tmp = b;
            b = w;
            w = tmp;
        }
    } else if (mode == 2) {
        int center = rnd.next(450, 550);
        int delta = rnd.next(-30, 30);
        b = center;
        w = center + delta;
    } else if (mode == 3) {
        b = rnd.next(900, 1000);
        w = rnd.next(900, 1000);
    } else if (mode == 4) {
        b = rnd.any(std::vector<int>{1, 2, 3, 999, 1000});
        w = rnd.next(1, 1000);
        if (rnd.next(0, 1)) {
            int tmp = b;
            b = w;
            w = tmp;
        }
    } else {
        b = rnd.next(1, 1000);
        w = rnd.next(1, 1000);
    }

    println(b, w);
    return 0;
}
