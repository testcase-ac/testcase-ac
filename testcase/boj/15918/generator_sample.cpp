#include "testlib.h"
#include <algorithm>
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int gap;

    if (mode == 0) {
        n = rnd.next(2, 5);
        gap = rnd.next(1, n);
    } else if (mode == 1) {
        n = 12;
        gap = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        gap = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        gap = n;
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        gap = rnd.any(std::vector<int>{1, n});
    } else {
        n = rnd.next(2, 12);
        gap = rnd.next(1, n);
    }

    int maxX = 2 * n - gap - 1;
    int x;
    if (mode == 3) {
        x = rnd.any(std::vector<int>{1, maxX});
    } else if (rnd.next(0, 3) == 0) {
        x = rnd.any(std::vector<int>{1, maxX});
    } else {
        x = rnd.next(1, maxX);
    }

    int y = x + gap + 1;
    println(n, x, y);

    return 0;
}
