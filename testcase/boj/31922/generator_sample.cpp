#include "testlib.h"
#include <algorithm>
#include <vector>

int clampPrize(int x) {
    if (x < 1) return 1;
    if (x > 500) return 500;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A = 1;
    int P = 1;
    int C = 1;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        A = rnd.next(1, 500);
        P = rnd.next(1, 500);
        C = rnd.next(1, 500);
    } else if (mode == 1) {
        A = rnd.next(1, 20);
        C = rnd.next(1, 20);
        P = rnd.next(clampPrize(A + C + 1), 500);
    } else if (mode == 2) {
        A = rnd.next(250, 500);
        C = rnd.next(250, 500);
        P = rnd.next(1, 500);
    } else if (mode == 3) {
        A = rnd.next(1, 499);
        C = rnd.next(1, 500 - A);
        P = A + C;
    } else if (mode == 4) {
        A = rnd.any(std::vector<int>{1, 2, 499, 500});
        P = rnd.any(std::vector<int>{1, 2, 499, 500});
        C = rnd.any(std::vector<int>{1, 2, 499, 500});
    } else if (mode == 5) {
        A = rnd.next(1, 500);
        C = rnd.next(1, 500);
        P = clampPrize(A + C + rnd.next(-3, 3));
    } else {
        A = rnd.next(1, 500);
        C = rnd.next(1, 500);
        P = rnd.next(1, 500);
        if (rnd.next(2)) std::swap(A, C);
    }

    println(A, P, C);
    return 0;
}
