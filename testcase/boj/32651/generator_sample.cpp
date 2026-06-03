#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = 2024 * rnd.next(1, 49);
    } else if (mode == 1) {
        n = 2024 * rnd.next(50, 494071);
    } else if (mode == 2) {
        int base = 2024 * rnd.next(1, 49);
        int delta = rnd.any(std::vector<int>{-2, -1, 1, 2});
        n = base + delta;
        if (n < 1) n = 1;
    } else if (mode == 3) {
        n = rnd.next(99990, 100010);
    } else if (mode == 4) {
        n = rnd.next(1, 100000);
        if (n % 2024 == 0) ++n;
    } else {
        n = rnd.next(100001, 1000000000);
    }

    println(n);
    return 0;
}
