#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 70);
    } else if (mode == 3) {
        n = rnd.next(71, 139);
    } else if (mode == 4) {
        n = 140;
    } else {
        n = rnd.any(std::vector<int>{2, 3, 4, 5, 10, 50, 100, 139, 140});
    }

    println(n);
    return 0;
}
