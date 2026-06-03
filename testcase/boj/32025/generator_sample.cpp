#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h;
    int w;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        h = w = rnd.next(5, 1000);
    } else if (mode == 1) {
        h = 5;
        w = rnd.next(5, 1000);
    } else if (mode == 2) {
        h = rnd.next(5, 1000);
        w = 1000;
    } else if (mode == 3) {
        h = rnd.next(5, 1000);
        int delta = rnd.next(-20, 20);
        w = std::min(1000, std::max(5, h + delta));
    } else {
        h = rnd.next(5, 1000);
        w = rnd.next(5, 1000);
    }

    if (rnd.next(0, 1) == 1)
        std::swap(h, w);

    println(h);
    println(w);

    return 0;
}
