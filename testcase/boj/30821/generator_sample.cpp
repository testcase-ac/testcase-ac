#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 5 + rnd.next(0, 3);
    } else if (mode == 1) {
        n = rnd.next(8, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 60);
    } else if (mode == 3) {
        n = rnd.next(61, 96);
    } else {
        n = 97 + rnd.next(0, 3);
    }

    println(n);
    return 0;
}
