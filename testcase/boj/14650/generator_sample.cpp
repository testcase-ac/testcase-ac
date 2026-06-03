#include "testlib.h"

#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    std::vector<int> boundary = {1, 2, 3, 8, 9};

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 9;
    } else if (mode == 2) {
        n = rnd.any(boundary);
    } else if (mode == 3) {
        n = rnd.next(1, 4);
    } else {
        n = rnd.next(5, 9);
    }

    println(n);
    return 0;
}
