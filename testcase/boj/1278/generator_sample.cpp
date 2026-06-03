#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = 17;
    } else if (mode <= 3) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(9, 17);
    }

    println(n);
    return 0;
}
