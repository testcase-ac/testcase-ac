#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.any(std::vector<int>{1, 2, 3, 9998, 9999, 10000});
    } else if (mode == 1) {
        n = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 2000);
    } else if (mode == 4) {
        n = rnd.next(2001, 9000);
    } else {
        n = rnd.next(9001, 10000);
    }

    println(n);
    return 0;
}
