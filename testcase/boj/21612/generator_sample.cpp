#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int b;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        b = rnd.next(80, 85);
    } else if (mode == 1) {
        b = rnd.next(96, 104);
    } else if (mode == 2) {
        b = rnd.next(195, 200);
    } else {
        b = rnd.next(80, 200);
    }

    println(b);
    return 0;
}
