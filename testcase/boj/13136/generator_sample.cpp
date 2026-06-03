#include "testlib.h"

#include <algorithm>
using namespace std;

int clampValue(int value) {
    return max(1, min(1000000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r;
    int c;
    int n;

    if (mode == 0) {
        n = 1;
        r = rnd.next(1, 30);
        c = rnd.next(1, 30);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        r = rnd.next(1, n);
        c = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(2, 50);
        r = n * rnd.next(1, 20);
        c = n * rnd.next(1, 20);
    } else if (mode == 3) {
        n = rnd.next(2, 50);
        r = n * rnd.next(1, 20) + rnd.next(1, n - 1);
        c = n * rnd.next(1, 20) + rnd.next(1, n - 1);
    } else if (mode == 4) {
        n = rnd.next(1, 1000);
        r = rnd.next(999000, 1000000);
        c = rnd.next(999000, 1000000);
    } else {
        n = rnd.next(1, 1000000);
        r = rnd.next(1, 1000000);
        c = rnd.next(1, 1000000);
    }

    println(clampValue(r), clampValue(c), clampValue(n));
    return 0;
}
