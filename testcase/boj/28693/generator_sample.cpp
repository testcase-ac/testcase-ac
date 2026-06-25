#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(6, 50);
    } else if (mode == 2) {
        n = rnd.next(51, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 999);
    } else if (mode == 4) {
        std::vector<int> boundaryValues = {1, 2, 3, 10, 100, 999, 1000};
        n = rnd.any(boundaryValues);
    } else {
        n = rnd.wnext(1000, 3) + 1;
    }

    println(n);
    return 0;
}
