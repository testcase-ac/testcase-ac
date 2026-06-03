#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int mode = rnd.next(0, 5);
    int n = 0;
    int a = 0;
    int b = 0;

    if (mode == 0) {
        n = rnd.next(0, 3);
        a = rnd.next(0, n);
        b = rnd.next(0, n);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        a = rnd.next(0, n);
        b = rnd.next(0, n);
    } else if (mode == 2) {
        n = rnd.next(1, 100);
        a = 0;
        b = rnd.next(0, n);
        if (rnd.next(0, 1)) swap(a, b);
    } else if (mode == 3) {
        n = rnd.next(1, 200);
        a = rnd.next(0, n);
        b = a;
    } else if (mode == 4) {
        n = rnd.next(maxN - 2000, maxN);
        a = rnd.next(0, min(n, 20));
        b = rnd.next(max(0, n - 20), n);
        if (rnd.next(0, 1)) swap(a, b);
    } else {
        n = rnd.next(1, maxN);
        int upper = min(n, 1000);
        a = rnd.next(0, upper);
        b = rnd.next(0, upper);
    }

    println(n, a, b);
    return 0;
}
