#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;

    if (mode == 0) {
        n = m = rnd.next(1, 10);
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(1, 10);
    } else if (mode == 2) {
        n = rnd.next(1, 10);
        m = 1;
    } else if (mode == 3) {
        n = 10;
        m = rnd.next(1, 10);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        m = 10;
    } else {
        n = rnd.next(1, 10);
        m = rnd.next(1, 10);
    }

    if (rnd.next(0, 1)) {
        swap(n, m);
    }

    println(n, m);
    return 0;
}
