#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int k;
    if (mode == 0) {
        k = rnd.next(1, 5);
    } else if (mode == 1) {
        k = rnd.next(246, 250);
    } else if (mode == 2) {
        k = rnd.next(1, 250);
    } else if (mode == 3) {
        k = rnd.wnext(250, -3) + 1;
    } else {
        k = rnd.wnext(250, 3) + 1;
    }

    println(k * 4);
    return 0;
}
