#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 35);
    } else if (mode == 2) {
        n = rnd.next(36, 70);
    } else if (mode == 3) {
        n = rnd.next(71, 90);
    } else {
        n = rnd.any(std::vector<int>{1, 2, 3, 4, 5, 89, 90});
    }

    println(n);
    return 0;
}
