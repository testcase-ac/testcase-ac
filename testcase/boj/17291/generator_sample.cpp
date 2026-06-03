#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        int edges[] = {1, 2, 3, 4, 5, 20};
        n = edges[rnd.next(0, 5)];
    } else if (mode == 1) {
        n = rnd.next(1, 6);
    } else if (mode == 2) {
        int base = rnd.next(1, 10);
        n = base * 2;
        if (rnd.next(0, 1) == 1) n--;
    } else {
        n = rnd.next(1, 20);
    }

    println(n);
    return 0;
}
