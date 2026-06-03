#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int k;

    if (mode == 0) {
        k = rnd.any(std::vector<int>{1, 2, 49, 50});
    } else if (mode == 1) {
        k = rnd.next(1, 10);
    } else if (mode == 2) {
        k = rnd.next(41, 50);
    } else {
        k = rnd.next(1, 50);
    }

    println(k);
    return 0;
}
