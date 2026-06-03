#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int x = 0;
    int y = 0;

    if (mode == 0) {
        x = 0;
        y = rnd.next(1, 1000000);
    } else if (mode == 1) {
        x = rnd.next(1, 1000000);
        y = 0;
    } else if (mode == 2) {
        x = y = rnd.next(1, 1000000);
    } else if (mode == 3) {
        x = rnd.next(0, 20);
        y = rnd.next(0, 20);
    } else if (mode == 4) {
        x = rnd.next(999980, 1000000);
        y = rnd.next(999980, 1000000);
    } else if (mode == 5) {
        vector<int> values = {0, 1, 2, 3, 999999, 1000000};
        x = rnd.any(values);
        y = rnd.any(values);
    } else {
        int base = rnd.next(1, 1000000);
        int delta = rnd.next(1, min(50, base));
        x = base;
        y = base - delta;
    }

    if (x == 0 && y == 0) {
        if (rnd.next(0, 1) == 0) {
            x = rnd.next(1, 20);
        } else {
            y = rnd.next(1, 20);
        }
    }

    if (rnd.next(0, 1) == 0) {
        swap(x, y);
    }

    println(x, y);
    return 0;
}
