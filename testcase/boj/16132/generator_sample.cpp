#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(std::vector<int>{1, 2, 3, 4, 7, 10, 28, 50});
    } else if (mode == 1) {
        n = rnd.next(1, 10);
    } else if (mode == 2) {
        int k = rnd.next(0, 12);
        n = 4 * k + rnd.any(std::vector<int>{1, 2});
        if (n < 1) n += 4;
        if (n > 50) n -= 4;
    } else if (mode == 3) {
        int k = rnd.next(0, 12);
        n = 4 * k + rnd.any(std::vector<int>{0, 3});
        if (n < 1) n += 4;
        if (n > 50) n -= 4;
    } else {
        n = rnd.next(1, 50);
    }

    println(n);
    return 0;
}
