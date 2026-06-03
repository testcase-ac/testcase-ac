#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 10);
    } else if (mode == 1) {
        n = rnd.any(std::vector<int>{2, 3, 4, 5, 10, 100000});
    } else if (mode == 2) {
        n = rnd.next(11, 100);
    } else if (mode == 3) {
        n = rnd.next(101, 1000);
    } else if (mode == 4) {
        n = rnd.next(1000, 100000);
    } else {
        n = 100000 - rnd.next(0, 20);
    }

    println(n);
    return 0;
}
