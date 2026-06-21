#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        k = rnd.next(80, 200);
    } else if (mode == 2) {
        n = rnd.next(80, 200);
        k = rnd.next(1, 20);
    } else if (mode == 3) {
        int base = rnd.next(1, 200);
        n = max(1, base + rnd.next(-10, 10));
        k = max(1, base + rnd.next(-10, 10));
    } else if (mode == 4) {
        n = rnd.next(1, 1000);
        k = rnd.next(1, 1000);
    } else if (mode == 5) {
        n = rnd.next(90000, 100000);
        k = rnd.next(1, 100);
    } else if (mode == 6) {
        n = rnd.next(1, 100);
        k = rnd.next(90000, 100000);
    } else {
        n = rnd.next(90000, 100000);
        k = rnd.next(90000, 100000);
    }

    println(n, k);
    return 0;
}
