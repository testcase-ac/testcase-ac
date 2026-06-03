#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static int clampValue(int x) {
    return max(1, min(1000000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int d1 = 1, d2 = 1, d3 = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int parity = rnd.next(0, 1);
        int a2 = 2 * rnd.next(1, 30) - parity;
        int b2 = 2 * rnd.next(1, 30) - parity;
        int c2 = 2 * rnd.next(1, 30) - parity;
        d1 = (a2 + b2) / 2;
        d2 = (a2 + c2) / 2;
        d3 = (b2 + c2) / 2;
    } else if (mode == 1) {
        int x = rnd.next(1, 80);
        int y = rnd.next(1, 80);
        d1 = x;
        d2 = y;
        d3 = x + y;
    } else if (mode == 2) {
        int x = rnd.next(2, 90);
        int y = rnd.next(1, x - 1);
        d1 = x;
        d2 = y;
        d3 = rnd.next(x + y + 1, min(1000000, x + y + 80));
    } else if (mode == 3) {
        int base = rnd.next(999900, 1000000);
        d1 = base;
        d2 = rnd.next(max(1, base - 60), 1000000);
        d3 = rnd.next(max(1, base - 60), 1000000);
    } else if (mode == 4) {
        d1 = rnd.next(1, 100);
        d2 = rnd.next(1, 100);
        d3 = rnd.next(1, 100);
    } else {
        vector<int> values = {1, 2, 3, rnd.next(1, 20), rnd.next(999980, 1000000)};
        d1 = rnd.any(values);
        d2 = rnd.any(values);
        d3 = rnd.any(values);
    }

    println(clampValue(d1), clampValue(d2), clampValue(d3));
    return 0;
}
