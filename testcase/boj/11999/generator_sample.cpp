#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x;
    int y;
    int m;

    if (mode == 0) {
        m = rnd.next(3, 40);
        y = rnd.next(2, m - 1);
        x = rnd.next(1, y - 1);
    } else if (mode == 1) {
        m = rnd.next(20, 150);
        y = rnd.next(max(2, m / 2), m - 1);
        x = rnd.next(1, y - 1);
    } else if (mode == 2) {
        int g = rnd.next(2, 20);
        int a = rnd.next(1, 12);
        int b = rnd.next(a + 1, 20);
        x = g * a;
        y = g * b;
        m = rnd.next(y + 1, min(1000, y + 5 * g + rnd.next(0, 80)));
    } else if (mode == 3) {
        m = rnd.next(900, 1000);
        y = rnd.next(max(2, m - 80), m - 1);
        x = rnd.next(max(1, y - 80), y - 1);
    } else if (mode == 4) {
        x = rnd.next(1, 60);
        int gap = rnd.next(1, 60);
        y = min(999, x + gap);
        if (x == y) --x;
        m = rnd.next(y + 1, min(1000, y + rnd.next(1, 200)));
    } else {
        m = rnd.next(3, 1000);
        y = rnd.next(2, m - 1);
        x = rnd.next(1, y - 1);
    }

    println(x, y, m);
    return 0;
}
