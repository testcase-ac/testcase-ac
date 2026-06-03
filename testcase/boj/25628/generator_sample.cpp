#include "testlib.h"
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = 1;
    int b = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(1, 100);
        b = rnd.next(1, 100);
    } else if (mode == 1) {
        b = rnd.next(1, 50);
        a = rnd.next(2 * b, 100);
    } else if (mode == 2) {
        a = rnd.next(2, 100);
        b = rnd.next(a / 2 + 1, 100);
    } else if (mode == 3) {
        a = 1;
        b = rnd.next(1, 100);
    } else if (mode == 4) {
        b = rnd.next(1, 50);
        a = rnd.next(std::max(1, 2 * b - 1), std::min(100, 2 * b + 1));
    } else {
        a = rnd.any(std::vector<int>{1, 2, 99, 100});
        b = rnd.any(std::vector<int>{1, 2, 99, 100});
    }

    println(a, b);
    return 0;
}
