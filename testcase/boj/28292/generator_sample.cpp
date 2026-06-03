#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        int edges[] = {1, 2, 3, 5, 6, 100};
        n = edges[rnd.next(0, 5)];
    } else if (mode == 1) {
        n = rnd.next(1, 8);
    } else if (mode == 2) {
        n = rnd.next(90, 100);
    } else if (mode == 3) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(1, 100);
    }

    println(n);
    return 0;
}
