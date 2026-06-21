#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(11, 1000);
    } else if (mode == 2) {
        int base = rnd.any(std::vector<int>{10007, 20014, 30021, 100000});
        n = base + rnd.next(-20, 20);
    } else if (mode == 3) {
        n = rnd.next(1000000, 1000000000);
    } else if (mode == 4) {
        n = 1000000000 - rnd.next(0, 1000);
    } else {
        n = rnd.next(1, 500000000) * 2 - rnd.next(0, 1);
    }

    println(n);
    return 0;
}
