#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 6;
    } else if (mode == 2) {
        n = rnd.next(2, 4);
    } else {
        n = rnd.next(1, 6);
    }

    println(n);
    return 0;
}
