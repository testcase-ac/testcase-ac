#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 1000);
    } else if (mode == 1) {
        n = rnd.next(1, 1000);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        m = rnd.next(1, 20);
    } else if (mode == 3) {
        int side = rnd.next(1, 1000);
        n = side;
        m = side;
    } else {
        n = rnd.next(950, 1000);
        m = rnd.next(950, 1000);
    }

    if (rnd.next(0, 1)) {
        swap(n, m);
    }

    println(n, m);
    return 0;
}
