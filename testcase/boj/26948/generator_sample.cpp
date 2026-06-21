#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 16);
    } else if (mode == 3) {
        n = rnd.next(17, 24);
    } else if (mode == 4) {
        n = rnd.any(std::vector<int>{1, 2, 3, 22, 23, 24});
    } else {
        n = rnd.next(1, 24);
    }

    println(n);
    return 0;
}
