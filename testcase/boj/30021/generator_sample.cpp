#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else if (mode <= 3) {
        n = rnd.next(3, 20);
    } else if (mode == 4) {
        n = rnd.any(std::vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    } else if (mode == 5) {
        n = rnd.next(21, 100);
    } else if (mode == 6) {
        n = rnd.next(101, 1000);
    } else {
        n = rnd.next(4500, 5000);
    }

    println(n);
    return 0;
}
