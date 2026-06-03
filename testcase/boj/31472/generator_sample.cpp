#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int sideHalf = 1;

    if (mode == 0) {
        sideHalf = rnd.any(std::vector<int>{1, 2, 3, 99, 100});
    } else if (mode == 1) {
        sideHalf = rnd.next(1, 10);
    } else if (mode == 2) {
        sideHalf = rnd.next(11, 40);
    } else if (mode == 3) {
        sideHalf = rnd.next(41, 100);
    } else {
        sideHalf = rnd.wnext(100, 2) + 1;
    }

    println(2 * sideHalf * sideHalf);
    return 0;
}
