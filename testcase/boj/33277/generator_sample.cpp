#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(638, 641);
    int mode = rnd.next(6);
    int m;

    if (mode == 0) {
        m = rnd.next(0, min(5, n));
    } else if (mode == 1) {
        m = n - rnd.next(0, min(5, n));
    } else if (mode == 2) {
        int minute = rnd.next(0, 1440);
        int delta = rnd.next(-2, 2);
        m = (minute * n) / 1440 + delta;
        m = max(0, min(n, m));
    } else if (mode == 3) {
        int hour = rnd.next(0, 24);
        int delta = rnd.next(-3, 3);
        m = (hour * 60 * n) / 1440 + delta;
        m = max(0, min(n, m));
    } else if (mode == 4) {
        m = rnd.next(max(0, n / 2 - 20), min(n, n / 2 + 20));
    } else {
        m = rnd.next(0, n);
    }

    println(n, m);
    return 0;
}
