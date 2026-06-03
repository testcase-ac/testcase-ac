#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int digits[3];
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        for (int i = 0; i < 3; ++i) digits[i] = rnd.next(0, 9);
    } else if (mode == 1) {
        int edge = rnd.next(0, 1) ? 9 : 0;
        for (int i = 0; i < 3; ++i) digits[i] = edge;
        digits[rnd.next(0, 2)] = rnd.next(0, 9);
    } else if (mode == 2) {
        int targetRemainder = 9;
        digits[0] = rnd.next(0, 9);
        digits[1] = rnd.next(0, 9);
        digits[2] = (targetRemainder - digits[0] - 3 * digits[1]) % 10;
        if (digits[2] < 0) digits[2] += 10;
    } else {
        digits[0] = rnd.next(0, 9);
        digits[1] = rnd.next(0, 9);
        digits[2] = rnd.next(0, 9);
        shuffle(digits, digits + 3);
    }

    for (int i = 0; i < 3; ++i) println(digits[i]);

    return 0;
}
