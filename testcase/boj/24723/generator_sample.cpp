#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 5;
    } else {
        n = rnd.next(2, 4);
    }

    println(n);
    return 0;
}
