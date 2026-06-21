#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int h;
    int w;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        h = 0;
        w = rnd.next(1, 200);
    } else if (mode == 1) {
        h = rnd.next(0, 5);
        w = rnd.next(1, 8);
    } else if (mode == 2) {
        h = rnd.next(1, 5);
        w = rnd.next(180, 200);
    } else if (mode == 3) {
        h = rnd.next(0, 5);
        w = rnd.next(1, 200);
    } else if (mode == 4) {
        h = rnd.next(4, 5);
        w = rnd.next(40, 120);
    } else {
        h = rnd.any(std::vector<int>{0, 1, 5});
        w = rnd.any(std::vector<int>{1, 2, 3, 199, 200});
    }

    println(h, w);
    return 0;
}
