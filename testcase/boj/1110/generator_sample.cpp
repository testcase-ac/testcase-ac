#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;

    if (mode == 0) {
        n = rnd.any(std::vector<int>{0, 1, 9, 10, 90, 99});
    } else if (mode == 1) {
        n = rnd.next(0, 9);
    } else if (mode == 2) {
        int digit = rnd.next(1, 9);
        n = rnd.any(std::vector<int>{digit * 10, digit * 11});
    } else {
        n = rnd.next(10, 99);
    }

    println(n);
    return 0;
}
