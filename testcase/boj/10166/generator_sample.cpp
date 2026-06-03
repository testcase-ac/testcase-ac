#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int d1 = 1;
    int d2 = 1;
    int mode = rnd.next(8);

    if (mode == 0) {
        d1 = d2 = rnd.next(1, 2000);
    } else if (mode == 1) {
        d1 = 1;
        d2 = rnd.next(1, 10);
    } else if (mode == 2) {
        d1 = rnd.next(1, 50);
        d2 = rnd.next(d1, 50);
    } else if (mode == 3) {
        d1 = rnd.next(1, 300);
        d2 = rnd.next(d1, 300);
    } else if (mode == 4) {
        d1 = rnd.next(1, 20);
        d2 = rnd.next(1980, 2000);
    } else if (mode == 5) {
        d2 = rnd.next(1800, 2000);
        d1 = rnd.next(max(1, d2 - 20), d2);
    } else if (mode == 6) {
        d1 = rnd.next(900, 1600);
        d2 = rnd.next(d1, min(2000, d1 + rnd.next(50, 400)));
    } else {
        d1 = rnd.next(1, 2000);
        d2 = rnd.next(d1, 2000);
    }

    println(d1, d2);
    return 0;
}
