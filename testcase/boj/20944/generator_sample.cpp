#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 10);
    } else if (mode == 1) {
        int values[] = {1, 2, 3, 999999, 1000000};
        n = values[rnd.next(0, 4)];
    } else if (mode == 2) {
        n = rnd.next(11, 1000);
    } else {
        n = rnd.next(1001, 1000000);
    }

    println(n);
    return 0;
}
