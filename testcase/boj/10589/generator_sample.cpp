#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 1;
    int m = 1;
    int mode = rnd.next(8);

    if (mode == 0) {
        n = rnd.any(std::vector<int>{1, 2, 49, 50});
        m = rnd.any(std::vector<int>{1, 2, 49, 50});
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 50);
    } else if (mode == 2) {
        n = rnd.next(1, 50);
        m = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 12) * 2;
        m = rnd.next(2, 12) * 2;
    } else if (mode == 4) {
        n = rnd.next(1, 25) * 2 - 1;
        m = rnd.next(1, 25) * 2 - 1;
    } else if (mode == 5) {
        n = rnd.next(1, 25) * 2;
        m = rnd.next(1, 25) * 2 - 1;
    } else if (mode == 6) {
        n = rnd.next(1, 25) * 2 - 1;
        m = rnd.next(1, 25) * 2;
    } else {
        n = rnd.next(1, 50);
        m = rnd.next(1, 50);
        if (rnd.next(2) == 0)
            std::swap(n, m);
    }

    println(n, m);
    return 0;
}
