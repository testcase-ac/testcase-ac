#include "testlib.h"

#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int x;
    int y;
    int k;
    int m;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        x = rnd.next(1, 6);
        y = rnd.next(1, 6);
        k = rnd.next(1, 8);
        m = rnd.next(1, min(200, x + y + rnd.next(0, 12)));
    } else if (mode == 1) {
        x = y = rnd.next(1, 100);
        k = rnd.next(1, 100);
        m = rnd.next(1, 200);
    } else if (mode == 2) {
        do {
            x = rnd.next(2, 100);
            y = rnd.next(2, 100);
        } while (gcd(x, y) != 1);
        k = rnd.next(1, 100);
        m = rnd.next(1, 200);
    } else if (mode == 3) {
        int g = rnd.next(2, 20);
        x = g * rnd.next(1, 100 / g);
        y = g * rnd.next(1, 100 / g);
        k = rnd.next(1, 100);
        m = rnd.next(1, 200);
    } else if (mode == 4) {
        x = rnd.next(1, 100);
        y = rnd.next(1, 100);
        int total = x + y;
        int delta = rnd.next(-10, 10);
        m = max(1, min(200, total + delta));
        k = rnd.next(1, 12);
    } else if (mode == 5) {
        x = rnd.next(90, 100);
        y = rnd.next(90, 100);
        k = rnd.next(90, 100);
        m = rnd.next(180, 200);
    } else {
        x = rnd.next(1, 100);
        y = rnd.next(1, 100);
        k = rnd.next(1, 100);
        m = rnd.next(1, 200);
    }

    if (rnd.next(0, 1)) {
        swap(x, y);
    }

    println(x, y, k, m);
    return 0;
}
