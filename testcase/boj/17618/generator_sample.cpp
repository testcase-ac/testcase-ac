#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    if (mode == 0)
        println(rnd.next(1, 100));
    else if (mode == 1)
        println(rnd.next(999900, 1000100));
    else
        println(rnd.next(9999900, 10000000));
}
