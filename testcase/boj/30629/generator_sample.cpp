#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = n * n / 4;
    } else if (mode == 2) {
        n = rnd.next(1, 20);
        int upper = n * n / 4;
        m = max(0, upper - rnd.next(0, min(upper, 5)));
    } else if (mode == 3) {
        n = rnd.next(1, 40);
        int upper = n * n / 4;
        m = rnd.next(0, min(upper, 10));
    } else if (mode == 4) {
        n = rnd.next(2, 80);
        int upper = n * n / 4;
        m = rnd.next(0, upper);
    } else {
        n = rnd.next(80, 200);
        int upper = n * n / 4;
        m = rnd.next(0, min(upper, 500));
    }

    println(n, m);
    return 0;
}
