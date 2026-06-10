#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(9, 12);
    } else if (mode == 2) {
        n = rnd.next(11, 25);
    } else if (mode == 3) {
        n = rnd.next(26, 75);
    } else if (mode == 4) {
        n = rnd.next(76, 100);
    } else {
        n = rnd.any(std::vector<int>{1, 10, 11, 100});
    }

    println(n);
    return 0;
}
