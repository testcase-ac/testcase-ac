#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.any(std::vector<int>{1, 2, 3, 4, 5, 10});
    } else if (mode == 2) {
        n = rnd.next(9, 40);
    } else if (mode == 3) {
        n = rnd.next(41, 200);
    } else if (mode == 4) {
        n = rnd.next(201, 1000);
    } else {
        n = rnd.next(1001, 5000);
    }

    println(n);
    return 0;
}
