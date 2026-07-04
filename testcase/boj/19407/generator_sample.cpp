#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode < 3) {
        t = mode;
    } else {
        t = rnd.next(0, 2);
    }

    println(t);
    return 0;
}
