#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int A;
    int B;

    if (mode == 0) {
        A = rnd.next(2, 5);
        B = rnd.next(1, 5);
    } else if (mode == 1) {
        B = rnd.next(1, 12);
        A = B + 1;
    } else if (mode == 2) {
        B = rnd.next(2, 20);
        A = rnd.next(2, B);
    } else if (mode == 3) {
        A = rnd.next(3, 25);
        B = rnd.next(1, A - 2);
    } else if (mode == 4) {
        A = rnd.next(90, 100);
        B = rnd.next(90, 100);
    } else {
        A = rnd.next(2, 100);
        B = rnd.next(1, 100);
    }

    println(A, B);
    return 0;
}
