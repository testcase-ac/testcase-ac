#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a;
    if (mode == 0) {
        a = -rnd.next(1, 20);
    } else if (mode == 1) {
        a = 1;
    } else if (mode == 2) {
        a = rnd.next(2, 20);
    } else if (mode == 3) {
        a = rnd.next(999999900, 1000000000);
    } else if (mode == 4) {
        a = -rnd.next(999999900, 1000000000);
    } else {
        a = rnd.next(2, 1000000000);
    }

    println(a);
    return 0;
}
