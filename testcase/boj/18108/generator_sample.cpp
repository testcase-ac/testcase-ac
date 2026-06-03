#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int y;

    if (mode == 0) {
        y = 1000;
    } else if (mode == 1) {
        y = 3000;
    } else if (mode == 2) {
        y = rnd.next(2538, 2544);
    } else {
        y = rnd.next(1000, 3000);
    }

    println(y);
    return 0;
}
