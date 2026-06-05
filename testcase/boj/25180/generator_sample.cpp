#include "testlib.h"
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1000000000;

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        int q = rnd.next(0, MAX_N / 18);
        n = q * 18;
        if (n == 0) n = 18;
    } else if (mode == 2) {
        int q = rnd.next(0, MAX_N / 18);
        int r = rnd.next(1, 9);
        n = q * 18 + r;
        if (n > MAX_N) n -= 18;
    } else if (mode == 3) {
        int q = rnd.next(0, MAX_N / 18);
        int r = rnd.any(std::vector<int>{11, 13, 15, 17});
        n = q * 18 + r;
        if (n > MAX_N) n -= 18;
    } else if (mode == 4) {
        int q = rnd.next(0, MAX_N / 18);
        int r = rnd.any(std::vector<int>{10, 12, 14, 16});
        n = q * 18 + r;
        if (n > MAX_N) n -= 18;
    } else if (mode == 5) {
        int delta = rnd.next(0, 200);
        n = MAX_N - delta;
    } else {
        n = rnd.next(1, MAX_N);
    }

    println(n);
    return 0;
}
