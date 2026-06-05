#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int R = 1;
    int C = 1;
    int K = 1;

    if (mode == 0) {
        R = 1;
        C = 1;
        K = rnd.next(1, 1000);
    } else if (mode == 1) {
        R = 1;
        C = rnd.next(2, 25);
        K = rnd.next(1, 12);
    } else if (mode == 2) {
        R = rnd.next(2, 25);
        C = 1;
        K = rnd.next(1, 12);
    } else if (mode == 3) {
        R = rnd.next(1, 13) * 2 - 1;
        C = rnd.next(1, 13) * 2 - 1;
        K = rnd.next(1, 12);
    } else if (mode == 4) {
        R = rnd.next(1, 25);
        C = rnd.next(1, 25);
        if (R * C % 2 == 1) {
            if (R < 25) {
                ++R;
            } else {
                --R;
            }
        }
        K = rnd.next(1, 12);
    } else if (mode == 5) {
        R = rnd.next(20, 80);
        C = rnd.next(20, 80);
        K = rnd.next(1, 1000);
    } else {
        R = rnd.next(900, 1000);
        C = rnd.next(900, 1000);
        K = rnd.next(900, 1000);
    }

    println(R, C, K);
    return 0;
}
