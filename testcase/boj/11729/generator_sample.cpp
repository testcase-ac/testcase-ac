#include "testlib.h"

#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    int n;
    if (mode == 0) {
        n = rnd.any(std::vector<int>{1, 2, 3, 4});
    } else if (mode == 1) {
        n = rnd.next(5, 8);
    } else {
        n = rnd.next(9, 10);
    }

    println(n);
    return 0;
}
