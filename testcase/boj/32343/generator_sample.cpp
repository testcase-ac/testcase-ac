#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int a;
    int b;

    if (mode == 0) {
        n = rnd.next(1, 10);
        a = rnd.next(0, 1) ? 0 : n;
        b = rnd.next(0, 1) ? 0 : n;
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        a = rnd.next(0, n);
        b = n - a;
    } else if (mode == 2) {
        n = rnd.next(1, 10);
        a = rnd.next(0, n);
        b = a;
    } else if (mode == 3) {
        n = rnd.next(1, 5);
        a = rnd.next(0, n);
        b = rnd.next(0, n);
    } else if (mode == 4) {
        n = rnd.next(6, 10);
        int center = n / 2;
        a = rnd.next(max(0, center - 2), min(n, center + 2));
        b = rnd.next(max(0, center - 2), min(n, center + 2));
    } else {
        n = rnd.next(1, 10);
        a = rnd.next(0, n);
        b = rnd.next(0, n);
    }

    println(n);
    println(a, b);

    return 0;
}
