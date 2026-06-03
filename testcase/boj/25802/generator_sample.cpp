#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = rnd.next(0, 9);
    int b = rnd.next(0, 9);
    if (a == 0 && b == 0) {
        if (rnd.next(2) == 0) {
            a = rnd.next(1, 9);
        } else {
            b = rnd.next(1, 9);
        }
    }

    println(a, b);
    return 0;
}
