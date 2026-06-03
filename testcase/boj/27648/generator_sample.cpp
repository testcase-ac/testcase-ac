#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = 1;
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 40);
    } else if (mode == 2) {
        n = rnd.next(1, 40);
        m = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    } else if (mode == 4) {
        n = rnd.next(800, 1000);
        m = rnd.next(1, 5);
        if (rnd.next(0, 1)) swap(n, m);
    } else if (mode == 5) {
        n = rnd.next(30, 120);
        m = rnd.next(30, 120);
    } else if (mode == 6) {
        n = rnd.next(900, 1000);
        m = rnd.next(900, 1000);
    } else {
        n = rnd.next(1, 1000);
        m = rnd.next(1, 1000);
    }

    int need = n + m - 1;
    int k;

    if (mode == 0) {
        k = 1;
    } else if (rnd.next(0, 99) < 60) {
        int delta = rnd.next(-3, 3);
        k = max(1, min(100000, need + delta));
    } else if (rnd.next(0, 99) < 75) {
        k = rnd.next(1, min(100000, max(1, need + 20)));
    } else {
        k = rnd.next(1, 100000);
    }

    println(n, m, k);
    return 0;
}
