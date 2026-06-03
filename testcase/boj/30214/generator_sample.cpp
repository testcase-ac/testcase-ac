#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int s1 = 0;
    int s2 = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        s2 = rnd.next(1, 100);
        s1 = 0;
    } else if (mode == 1) {
        s2 = rnd.next(1, 50) * 2;
        s1 = s2 / 2;
    } else if (mode == 2) {
        s2 = rnd.next(3, 100);
        s1 = rnd.next(0, (s2 - 1) / 2);
    } else if (mode == 3) {
        s2 = rnd.next(1, 100);
        s1 = rnd.next((s2 + 1) / 2, s2);
    } else if (mode == 4) {
        s2 = rnd.next(90, 100);
        s1 = rnd.next(0, s2);
    } else {
        s2 = rnd.next(1, 100);
        s1 = rnd.next(0, s2);
    }

    println(s1, s2);
    return 0;
}
