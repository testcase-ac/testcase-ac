#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.any(std::vector<int>{1, 2, 3, 10, 100, 1000, 10000});
    } else if (mode == 2) {
        n = rnd.next(7, 100);
    } else if (mode == 3) {
        n = rnd.next(101, 2000);
    } else {
        n = rnd.next(2001, 10000);
    }

    println(n);
    return 0;
}
